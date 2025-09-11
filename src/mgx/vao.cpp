#include <mgx/vao.hpp>

namespace mgx {
	vao::vao() {
		GLCall( glGenVertexArrays(1, &id) );
	}

	vao::~vao() {
		Unbind();
		GLCall( glDeleteVertexArrays(1, &id) );
		if (m_vbo)
			m_vbo->Destroy();
			delete m_vbo;
		if (m_ibo)
			m_ibo->Destroy();
			delete m_ibo;
		if (m_blo)
			delete m_blo;
	}

	void vao::Bind() const {
		GLCall( glBindVertexArray(id) );
	}
	
	void vao::Unbind() const {
		GLCall( glBindVertexArray(0) );
	}
}