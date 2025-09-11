#pragma once

#include <string>
#include <unordered_map>

#include <GLM/glm.hpp>
#include <error.hpp>

namespace mgx {
	class shader {
	private:
		struct source_strs {
			std::string vs_source;
			std::string fs_source;
		};
		unsigned int id;

		std::unordered_map<std::string, unsigned int> uniform_map;

	public:
		shader();
		~shader();

		void LoadFromFile(const std::string& file_path);

		void Bind() const;
		void Unbind() const;

		void AssertShaderValid(unsigned int shader_id);
		void AssertProgramValid(unsigned int program_id);

		void SetUniform1i(const std::string& name, int v0);
		void SetUniform1f(const std::string& name, float v0);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

		void SetUniformMat4f(const std::string& name, glm::mat4& matrix);

		void PrintSource(source_strs* source);

	private:
		source_strs ParseShaderFile(const std::string& file_path);
		unsigned int CompileShaderSource(unsigned int shader_type, const std::string& source_code);
		int GetUniformLocation(const std::string& name);
	};
};