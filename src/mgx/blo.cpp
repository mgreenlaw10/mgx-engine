#include <mgx/blo.hpp>

#include <error.hpp>
#include <cstdint> // uintptr_t

namespace mgx {
	/**
	 * blo::Compile();
	 * 
	 * Call this AFTER adding all vertex attributes to
	 * automatically enable and init all vertex attributes.
	 */
	void blo::Compile() const {
		unsigned int offset = 0;
		for (size_t layout_id = 0; layout_id < elements.size(); layout_id++) {
			GLCall( glEnableVertexAttribArray(layout_id) );
			GLCall( glVertexAttribPointer (
				layout_id,
				elements[layout_id].count,
				elements[layout_id].gl_type,
				elements[layout_id].normal,
				this->stride,
				reinterpret_cast<const void*>(static_cast<uintptr_t>(offset))
			));
			offset += elements[layout_id].count * 
			          sizeof(elements[layout_id].gl_type);
		}
	}

	/**
	 * blo::AddAttrib<typename T>(unsigned int count);
	 * 
	 * Call BEFORE compiling to register a new vertex attribute with 
	 * @count number of values of type @T.
	 */
	template<typename T>
	void blo::AddAttrib(unsigned int count) {
		//static_assert(false);
	}

	template<>
	void blo::AddAttrib<float>(unsigned int count) {
		this->elements.push_back( {GL_FLOAT, count, GL_FALSE} );
		this->stride += count * sizeof(float);
	}
	template<>
	void blo::AddAttrib<double>(unsigned int count) {
		this->elements.push_back( {GL_DOUBLE, count, GL_FALSE} );
		this->stride += count * sizeof(double);
	}
	template<>
	void blo::AddAttrib<int>(unsigned int count) {
		this->elements.push_back( {GL_INT, count, GL_FALSE} );
		this->stride += count * sizeof(int);
	}
	template<>
	void blo::AddAttrib<unsigned int>(unsigned int count) {
		this->elements.push_back( {GL_UNSIGNED_INT, count, GL_FALSE} );
		this->stride += count * sizeof(unsigned int);
	}
	template<>
	void blo::AddAttrib<unsigned char>(unsigned int count) {
		this->elements.push_back( {GL_UNSIGNED_BYTE, count, GL_FALSE} );
		this->stride += count * sizeof(unsigned char);
	}
};
