#pragma once

#include <mgx/vao.hpp>
#include "mgx/vbo.hpp"
#include "mgx/ibo.hpp"
#include "mgx/blo.hpp"
#include "mgx/shader.hpp"
#include "mgx/texture.hpp"
#include "mgx/camera.hpp"
#include "mgx/mesh.hpp"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include <string>
#include <memory>

#include <unordered_map>

namespace mgx
{
	class Renderer
	{
	private:

		enum class CacheID
		{
			QUAD_CLEARCOLOR     = 0,
			QUAD_TEXTURE        = 1,
			CUBE_CLEARCOLOR		= 2,
		};

		GLuint vao_cache[10];
		void LoadVAOCache();

		// Shaders should remain encapsulated on CPU
		// because they cache their own uniforms.
		mgx::shader* shader_cache[10];
		void LoadShaderCache();

		// define perspective frustum
		glm::mat4 projection = 
			glm::perspective(glm::radians(45.0f), 1200.0f / 900.0f, 0.1f, 100.0f);

		// define view coordinate system
		mgx::Camera3D camera;

	public:

		Renderer(const mgx::Camera3D& _camera);

		inline void SetCamera(const mgx::Camera3D& _camera) {
			camera = _camera;
		}

		inline mgx::Camera3D& GetCamera() {
			return camera;
		}
		
		/***********************************************/

		void DrawMeshes(const unsigned int mesh_vao,
						const mgx::MeshInstance* mesh_data,
						const unsigned int mesh_count,
						const mgx::texture* textures,
						const unsigned int texture_count);

		void DrawMeshesColor (const unsigned int mesh_vao,
							  const mgx::MeshInstance* mesh_data,
							  const unsigned int mesh_count,
							  const glm::vec4* colors,
							  const unsigned int color_count); 

		void DrawQuadCC(float _x, 
					    float _y,
					    float _z, 
					    float _w, 
					    float _h, 
					    const glm::vec4& _color = {1.0f, 0.0f, 0.0f, 1.0f});

		void DrawQuadTexture(float _x, 
				     		 float _y, 
				     		 float _z,
					     	 float _w, 
					     	 float _h, 
					     	 const mgx::texture& _texture);

		void SetVPDimension(int new_width, int new_height);

		void Clear() const;
	};
};