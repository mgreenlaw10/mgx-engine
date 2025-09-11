#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include <error.hpp>

/**
 * VertexBufferObject
 */ 
namespace mgx {
	class vbo {
	private:
		unsigned int id;

	public:
		vbo(const void* data, unsigned int size);
		~vbo();

		void Bind() const;
		void Unbind() const;

		inline void Destroy() {
			GLCall( glDeleteBuffers(1, &id) );
		}
	};
};