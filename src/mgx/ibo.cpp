#include <mgx/ibo.hpp>

namespace mgx {
	ibo::ibo(const void* _data, unsigned int _count): count(_count) {
		GLCall( glGenBuffers(1, &id) );
		Bind();
		GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(unsigned int), _data, GL_STATIC_DRAW) );
	}
	ibo::~ibo() {
		Unbind();
	}
	void ibo::Bind() const {
		GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id) );
	}
	void ibo::Unbind() const {
		GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) ); 
	}
};