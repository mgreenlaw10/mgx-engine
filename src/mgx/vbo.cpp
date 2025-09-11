#include <mgx/vbo.hpp>

namespace mgx {
	vbo::vbo(const void* data, unsigned int size) {
		GLCall( glGenBuffers(1, &id) );
		Bind();
		GLCall( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) );
	}
	vbo::~vbo() {
		Unbind();
	}
	void vbo::Bind() const {
		GLCall( glBindBuffer(GL_ARRAY_BUFFER, id) );
	}
	void vbo::Unbind() const {		
		GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
	}
};