#pragma once

#define GLM_FORCE_SWIZZLE
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include <error.hpp>

#include <cstdint> // uintptr_t



namespace mgx {

	// abstract mesh class. load specific meshes in child class constructors
	struct Mesh {

		unsigned int vao;

		Mesh() {
			GLCall( glGenVertexArrays(1, &vao) );
		}

		~Mesh() {
			GLCall( glDeleteVertexArrays(1, &vao) );
		}
	};

	// actual mesh implementation
	struct CubeM : public Mesh {

		static constexpr int VBO_SIZE = 180 * sizeof(float);
		static constexpr int STRIDE = 5 * sizeof(float);
		static constexpr std::uintptr_t OFFSET = 3 * sizeof(float);

		CubeM() {

			float VBO_DATA[180] = {
			    -0.5f, -0.5f, -0.5f,  	0.0f, 0.0f,
			     0.5f, -0.5f, -0.5f,  	1.0f, 0.0f,
			     0.5f,  0.5f, -0.5f,  	1.0f, 1.0f,
			     0.5f,  0.5f, -0.5f,  	1.0f, 1.0f,
			    -0.5f,  0.5f, -0.5f,  	0.0f, 1.0f,
			    -0.5f, -0.5f, -0.5f,  	0.0f, 0.0f,

			    -0.5f, -0.5f,  0.5f,  	0.0f, 0.0f,
			     0.5f, -0.5f,  0.5f,  	1.0f, 0.0f,
			     0.5f,  0.5f,  0.5f,  	1.0f, 1.0f,
			     0.5f,  0.5f,  0.5f,  	1.0f, 1.0f,
			    -0.5f,  0.5f,  0.5f,  	0.0f, 1.0f,
			    -0.5f, -0.5f,  0.5f,  	0.0f, 0.0f,

			    -0.5f,  0.5f,  0.5f,  	1.0f, 0.0f,
			    -0.5f,  0.5f, -0.5f,  	1.0f, 1.0f,
			    -0.5f, -0.5f, -0.5f,  	0.0f, 1.0f,
			    -0.5f, -0.5f, -0.5f,  	0.0f, 1.0f,
			    -0.5f, -0.5f,  0.5f,  	0.0f, 0.0f,
			    -0.5f,  0.5f,  0.5f,  	1.0f, 0.0f,

			     0.5f,  0.5f,  0.5f,  	1.0f, 0.0f,
			     0.5f,  0.5f, -0.5f,  	1.0f, 1.0f,
			     0.5f, -0.5f, -0.5f,  	0.0f, 1.0f,
			     0.5f, -0.5f, -0.5f,  	0.0f, 1.0f,
			     0.5f, -0.5f,  0.5f,  	0.0f, 0.0f,
			     0.5f,  0.5f,  0.5f,  	1.0f, 0.0f,

			    -0.5f, -0.5f, -0.5f,  	0.0f, 1.0f,
			     0.5f, -0.5f, -0.5f,  	1.0f, 1.0f,
			     0.5f, -0.5f,  0.5f,  	1.0f, 0.0f,
			     0.5f, -0.5f,  0.5f,  	1.0f, 0.0f,
			    -0.5f, -0.5f,  0.5f,  	0.0f, 0.0f,
			    -0.5f, -0.5f, -0.5f,  	0.0f, 1.0f,

			    -0.5f,  0.5f, -0.5f,  	0.0f, 1.0f,
			     0.5f,  0.5f, -0.5f,  	1.0f, 1.0f,
			     0.5f,  0.5f,  0.5f,  	1.0f, 0.0f,
			     0.5f,  0.5f,  0.5f,  	1.0f, 0.0f,
			    -0.5f,  0.5f,  0.5f,  	0.0f, 0.0f,
			    -0.5f,  0.5f, -0.5f,  	0.0f, 1.0f
			};

			GLuint vbo;

			GLCall( glBindVertexArray(vao) );

			GLCall( glGenBuffers(1, &vbo) );
			GLCall( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
			GLCall( glBufferData(GL_ARRAY_BUFFER, VBO_SIZE, VBO_DATA, GL_STATIC_DRAW) );

			GLCall( glEnableVertexAttribArray(0) );
			GLCall( glEnableVertexAttribArray(1) );

			GLCall( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE, nullptr) );
			GLCall( glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE, reinterpret_cast<const void*>(OFFSET)) );

			GLCall( glBindVertexArray(0) );
			// should i delete vbo?
		}
	};

	// describes how to draw a mesh
	struct MeshInstance {
		
		// position
		glm::vec3 position  = glm::vec3(0.0f);
		glm::vec3 size 		= glm::vec3(1.0f);

		// rotation
		float rotation_rads 	= 0.0f;
		glm::vec3 rotation_axis = glm::vec3(1.0f, 0.0f, 0.0f); // must be normal

		// texture
		
		int texture_slot = -1;

		glm::mat4 ModelMatrix() const {
			return glm::translate	(glm::mat4(1.0f), position) * 
				   glm::scale		(glm::mat4(1.0f), size) *
				   glm::rotate		(glm::mat4(1.0f), rotation_rads, glm::normalize(rotation_axis));
		}
	};
}



	


