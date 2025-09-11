#include "mgx/renderer.hpp"

#include "scene/scene_manager.hpp" // window resize event
#include "mgx/engine.hpp"

#include <cstdint> // uintptr_t

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp> // print mat4

namespace mgx {

	Renderer::Renderer(const mgx::Camera3D& _camera): camera(_camera) {
		LoadVAOCache();
		LoadShaderCache();
	}

	/*************************************************************************************/
	/*                                    VAO CACHE                      											
	/*************************************************************************************/

	void Renderer::LoadVAOCache()
	{
		{	// QUAD CLEAR COLOR
			GLuint QUAD_CLEARCOLOR_vao;
			GLuint QUAD_CLEARCOLOR_vbo;
			GLuint QUAD_CLEARCOLOR_ibo;

			constexpr int VB_SIZE = sizeof(GLfloat) * 16;
			constexpr int IB_SIZE = sizeof(GLuint)  * 6;
			constexpr int STRIDE  = sizeof(GLfloat) * 4;

			float _vb[] = {
			   -0.5f,-0.5f, 0.0f, 1.0f,
			   -0.5f, 0.5f, 0.0f, 1.0f,
				0.5f,-0.5f, 0.0f, 1.0f,
				0.5f, 0.5f, 0.0f, 1.0f
			};
			unsigned int _ib[] = {
				0, 1, 2, 
				1, 2, 3
			};

			GLCall( glGenVertexArrays(1, &QUAD_CLEARCOLOR_vao) );
			GLCall( glBindVertexArray(QUAD_CLEARCOLOR_vao) );

			GLCall( glGenBuffers(1, &QUAD_CLEARCOLOR_vbo) );
			GLCall( glGenBuffers(1, &QUAD_CLEARCOLOR_ibo) );

			GLCall( glBindBuffer(GL_ARRAY_BUFFER, QUAD_CLEARCOLOR_vbo) );
			GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QUAD_CLEARCOLOR_ibo) );

			GLCall( glBufferData(GL_ARRAY_BUFFER, VB_SIZE, _vb, GL_STATIC_DRAW) );
			GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, IB_SIZE, _ib, GL_STATIC_DRAW) );

			GLCall( glEnableVertexAttribArray(0) ); // no need for blo with one attribute
		   	GLCall( glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, STRIDE, nullptr) );

		   	GLCall( glBindVertexArray(0) );

			vao_cache[(int)CacheID::QUAD_CLEARCOLOR] = QUAD_CLEARCOLOR_vao;
		}
		{	// QUAD TEXTURE
			GLuint QUAD_TEXTURE_vao;
			GLuint QUAD_TEXTURE_vbo;
			GLuint QUAD_TEXTURE_ibo;

			constexpr int VB_SIZE = sizeof(GLfloat) * 24;
			constexpr int IB_SIZE = sizeof(GLuint)  * 6;
			constexpr int STRIDE  = sizeof(GLfloat) * 6;

			float _vb[] = {
			   -0.5f,-0.5f, 0.0f, 1.0f, 	0.0f, 0.0f,
			   -0.5f, 0.5f, 0.0f, 1.0f, 	0.0f, 1.0f,
				0.5f,-0.5f, 0.0f, 1.0f, 	1.0f, 0.0f,
				0.5f, 0.5f, 0.0f, 1.0f, 	1.0f, 1.0f
			};
			unsigned int _ib[] = {
				0, 1, 2, 
				1, 2, 3
			};

			GLCall( glGenVertexArrays(1, &QUAD_TEXTURE_vao) );
			GLCall( glBindVertexArray(QUAD_TEXTURE_vao) );

			GLCall( glGenBuffers(1, &QUAD_TEXTURE_vbo) );
			GLCall( glGenBuffers(1, &QUAD_TEXTURE_ibo) );

			GLCall( glBindBuffer(GL_ARRAY_BUFFER, QUAD_TEXTURE_vbo) );
			GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QUAD_TEXTURE_ibo) );

			GLCall( glBufferData(GL_ARRAY_BUFFER, VB_SIZE, _vb, GL_STATIC_DRAW) );
			GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, IB_SIZE, _ib, GL_STATIC_DRAW) );

			mgx::blo QUAD_TEXTURE_blo;
			QUAD_TEXTURE_blo.AddAttrib<float>(4); // position
			QUAD_TEXTURE_blo.AddAttrib<float>(2); // texture coords
			QUAD_TEXTURE_blo.Compile();

		   	GLCall( glBindVertexArray(0) );

			vao_cache[(int)CacheID::QUAD_TEXTURE] = QUAD_TEXTURE_vao;
		}
	}

	/*************************************************************************************/
	/*                                   SHADER CACHE                      											
	/*************************************************************************************/

	void Renderer::LoadShaderCache()
	{
		mgx::shader* QUAD_CLEARCOLOR_shader = new mgx::shader();
		QUAD_CLEARCOLOR_shader->LoadFromFile("res/shader/color_quad.shader");
		shader_cache[(int)CacheID::QUAD_CLEARCOLOR] = QUAD_CLEARCOLOR_shader;

		mgx::shader* QUAD_TEXTURE_shader = new mgx::shader();
		QUAD_TEXTURE_shader->LoadFromFile("res/shader/texture_quad.shader");
		shader_cache[(int)CacheID::QUAD_TEXTURE] = QUAD_TEXTURE_shader;
	}

	/*************************************************************************************/
	/*                                   DRAW CALLS                      											
	/*************************************************************************************/

	void Renderer::DrawMeshes (
		const unsigned int mesh_vao,
		const mgx::MeshInstance* mesh_data,
		const unsigned int mesh_count,
		const mgx::texture* textures,
		const unsigned int texture_count
	) {
		GLCall( glBindVertexArray(mesh_vao) );

		for (int i = 0; i < texture_count; i++)
			textures[i].Bind(i);
		
		shader_cache[(int)CacheID::QUAD_TEXTURE]->Bind();

		for (int i = 0; i < mesh_count; i++) {
			
			glm::mat4 mvp = glm::mat4(this->projection * camera.GetViewMatrix() * mesh_data[i].ModelMatrix());

			shader_cache[(int)CacheID::QUAD_TEXTURE]->SetUniform1i("u_Texture", mesh_data[i].texture_slot);
			shader_cache[(int)CacheID::QUAD_TEXTURE]->SetUniformMat4f("u_MVP", mvp);

			GLCall( glDrawArrays(GL_TRIANGLES, 0, 36) );
		}
	}

	void Renderer::DrawMeshesColor (
		const unsigned int mesh_vao,
		const mgx::MeshInstance* mesh_data,
		const unsigned int mesh_count,
		const glm::vec4* colors,
		const unsigned int color_count
	) {
		GLCall( glBindVertexArray(mesh_vao) );

		shader_cache[(int)CacheID::QUAD_CLEARCOLOR]->Bind();

		for (int i = 0; i < mesh_count; i++) {
			
			glm::mat4 mvp = glm::mat4(this->projection * camera.GetViewMatrix() * mesh_data[i].ModelMatrix());

			shader_cache[(int)CacheID::QUAD_CLEARCOLOR]->SetUniform4f("u_Color", colors[mesh_data[i].texture_slot].r,
																				 colors[mesh_data[i].texture_slot].g,
																				 colors[mesh_data[i].texture_slot].b,
																				 colors[mesh_data[i].texture_slot].a);

			shader_cache[(int)CacheID::QUAD_CLEARCOLOR]->SetUniformMat4f("u_MVP", mvp);

			GLCall( glDrawArrays(GL_TRIANGLES, 0, 36) );
		}
	}



	void Renderer::DrawQuadCC(float _x, float _y, float _z, float _w, float _h, const glm::vec4& _color) 
	{
	   	GLCall( glBindVertexArray(vao_cache[(int)CacheID::QUAD_CLEARCOLOR]) );
	 
	   	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(_x, _y, _z)) * 
	   					  glm::scale    (glm::mat4(1.0f), glm::vec3(_w, _h, 1.0f));

	   	glm::mat4 view = camera.GetViewMatrix();

	   	auto mvp = glm::mat4(this->projection * view * model);

	   	shader_cache[(int)CacheID::QUAD_CLEARCOLOR]->Bind();
	   	shader_cache[(int)CacheID::QUAD_CLEARCOLOR]->SetUniformMat4f("u_MVP", mvp);
	    shader_cache[(int)CacheID::QUAD_CLEARCOLOR]->SetUniform4f   ("u_Color", _color.x, _color.y, _color.z, _color.w);

		GLCall( glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr) );
	}

	void Renderer::DrawQuadTexture(float _x, float _y, float _z, float _w, float _h, const mgx::texture& _texture) 
	{
	   	GLCall( glBindVertexArray(vao_cache[(int)CacheID::QUAD_TEXTURE]) );

	   	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(_x, _y, _z)) * 
	   					  glm::scale    (glm::mat4(1.0f), glm::vec3(_w, _h, 1.0f));

	   	glm::mat4 view = camera.GetViewMatrix();

	   	auto mvp = glm::mat4(this->projection * view * model);

		_texture.Bind(0);
	   	shader_cache[(int)CacheID::QUAD_TEXTURE]->Bind();
	   	shader_cache[(int)CacheID::QUAD_TEXTURE]->SetUniformMat4f("u_MVP", mvp);
	    shader_cache[(int)CacheID::QUAD_TEXTURE]->SetUniform1i 	 ("u_Texture", 0);

		GLCall( glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr) );
	}

	/*************************************************************************************/
	/*                                  RENDERER UTIL                      											
	/*************************************************************************************/

	void Renderer::SetVPDimension(int new_width, int new_height) {

		projection = glm::perspective(glm::radians(45.0f), (float)(new_width) / (float)(new_height), 0.1f, 100.0f);
		GLCall( glViewport(0, 0, new_width, new_height) );

		SceneManager::GetInstance()->GetCurrentScene()->OnRender();
		//SceneManager::GetInstance()->GetCurrentScene()->OnImGuiRender(); doesn't work currently

		glfwSwapBuffers(Engine::GetInstance()->GetWindow());
	}

	void Renderer::Clear() const {
		GLCall( glClear(GL_COLOR_BUFFER_BIT) );
	}
}