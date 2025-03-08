#pragma once

#include <error.hpp>
#include <mgx/blo.hpp>
#include <mgx/vbo.hpp>
#include <mgx/ibo.hpp>

/**
 * VertexArrayObject
 */ 
namespace mgx {
	class vao {
	private:
		unsigned int id;
		vbo* m_vbo = nullptr;
		ibo* m_ibo = nullptr;
		blo* m_blo = nullptr;
		
	public:
		vao();
		~vao();

		inline void SetVBO(vbo* _vbo) {
			m_vbo = _vbo;
			_vbo->Bind();
		}
		inline vbo* GetVBO() const {return m_vbo;}

		inline void SetIBO(ibo* _ibo) {
			m_ibo = _ibo;
			_ibo->Bind();
		}
		inline ibo* GetIBO() const {return m_ibo;}

		inline void SetBLO(blo* _blo) {
			m_blo = _blo;
			_blo->Compile();
		}
		inline blo* GetBLO() const {return m_blo;}

		void Bind() const;
		void Unbind() const;
	};
};