#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include <error.hpp>

/**
 * IndexBufferObject
*/
namespace mgx {
	class ibo {
	private:
		unsigned int id;
		unsigned int count;

	public:
		ibo(const void* data, unsigned int count);
		~ibo();

		void Bind() const;
		void Unbind() const;

		inline void Destroy() {
			GLCall( glDeleteBuffers(1, &id) );
		}

		inline unsigned int GetCount() const { return count; }
	};
};