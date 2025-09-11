#include <mgx/shader.hpp>

#include <fstream>
#include <sstream>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include <error.hpp>

namespace mgx {

	shader::shader() {
		GLCall( id = glCreateProgram() );
	}

	shader::~shader() {
		Unbind();
		GLCall( glDeleteProgram(id) );
	}

	/*************************************************************************************/
	/*                             SHADER FILE PARSE/COMPILE                      											
	/*************************************************************************************/

	void shader::LoadFromFile(const std::string& file_path) {
		source_strs src = ParseShaderFile(file_path);
		//PrintSource(&src);

		unsigned int vs_id = CompileShaderSource(GL_VERTEX_SHADER, src.vs_source);
		unsigned int fs_id = CompileShaderSource(GL_FRAGMENT_SHADER, src.fs_source);

		GLCall( glAttachShader(id, vs_id) );
    	GLCall( glAttachShader(id, fs_id) );

    	GLCall( glLinkProgram(id) );
    	GLCall( glValidateProgram(id) );

    	AssertProgramValid(id);

    	GLCall( glDeleteShader(vs_id) );
    	GLCall( glDeleteShader(fs_id) );
	}

	shader::source_strs shader::ParseShaderFile(const std::string& file_path) {
		enum class shader_type {
			null = -1,
			vertex = 0,
			fragment = 1
		};

		std::ifstream file(file_path);
		std::string line;
		std::stringstream stream[2];

		shader_type current_type = shader_type::null;

		while (getline(file, line)) {
			if (line.find("#shader") != std::string::npos) {

				if (line.find("vertex") != std::string::npos) 
                	current_type = shader_type::vertex;
            	else if (line.find("fragment") != std::string::npos) 
                	current_type = shader_type::fragment;
	        }
	        else if (current_type != shader_type::null) 
	            stream[(int)current_type] << line << '\n';
	    }
    	return { stream[0].str(), stream[1].str() };
	}

	unsigned int shader::CompileShaderSource(unsigned int shader_type, const std::string& source_code) {
		unsigned int shader_id = glCreateShader(shader_type);

		const char* source_cstr = source_code.c_str();
	    GLCall( glShaderSource(shader_id, 1, &source_cstr, nullptr) );
	    GLCall( glCompileShader(shader_id));

	    AssertShaderValid(shader_id);
	    
    	return shader_id;
	}

	/*************************************************************************************/
	/*                              SHADER VALIDITY CHECK                      											
	/*************************************************************************************/

	void shader::AssertShaderValid(unsigned int shader_id) {
		int result;
	    GLCall( glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result) );

	    if (result == GL_FALSE) {
	        int len;
	        GLCall( glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len));
	        char* message = (char*)alloca(len * sizeof(char));
	        GLCall( glGetShaderInfoLog(shader_id, len, &len, message) );

	        std::cout << "Failed to compile shader:" << std::endl;
	        std::cout << message << std::endl;
	        GLCall( glDeleteShader(shader_id) );
	        ASSERT(false);
	    }
	}

	void shader::AssertProgramValid(unsigned int program_id) {
		int result;
	    GLCall( glGetProgramiv(program_id, GL_LINK_STATUS, &result) );

	    if (result == GL_FALSE) {
	        int len;
	        GLCall( glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &len));
	        char* message = (char*)alloca(len * sizeof(char));
	        GLCall( glGetShaderInfoLog(program_id, len, &len, message) );

	        std::cout << "Failed to validate program:" << std::endl;
	        std::cout << message << std::endl;
	        GLCall( glDeleteProgram(program_id) );
	        ASSERT(false);
	    }
	}

	/*************************************************************************************/
	/*                               SHADER BIND/UNBIND                      											
	/*************************************************************************************/

	void shader::Bind() const {
		GLCall( glUseProgram(id) );
	}

	void shader::Unbind() const {
		GLCall( glUseProgram(0) );
	}

	/*************************************************************************************/
	/*                                   SET UNIFORM                      											
	/*************************************************************************************/
		
	void shader::SetUniform1i(const std::string& name, int v0) {
	    GLCall( glUniform1i(GetUniformLocation(name), v0) );
	}

	void shader::SetUniform1f(const std::string& name, float v0) {
	    GLCall( glUniform1f(GetUniformLocation(name), v0) );
	}

	void shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
		GLCall( glUniform4f(GetUniformLocation(name), v0, v1, v2, v3) );
	}

	void shader::SetUniformMat4f(const std::string& name, glm::mat4& matrix) {
	    GLCall( glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]) );
	}

	int shader::GetUniformLocation(const std::string& name) {
		if (uniform_map.find(name) != uniform_map.end())
			return uniform_map[name];

		GLCall( int location = glGetUniformLocation(id, name.c_str()) );
		if (location == -1) 
			std::cout << "WARNING: uniform " << name << " doesn't exist" << std::endl;
		
		uniform_map[name] = location;
		return location;
	}

	/*************************************************************************************/
	/*                                 DEBUG FUNCTIONS                      											
	/*************************************************************************************/

	void shader::PrintSource(source_strs* source) {
		std::cout << "#shader vertex" << std::endl;
	    std::cout << source->vs_source << std::endl;
	    std::cout << "#shader fragment" << std::endl;
	    std::cout << source->fs_source << std::endl;
	}
};