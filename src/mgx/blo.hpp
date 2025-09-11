#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include <vector>

/**
 * BufferLayoutObject
 */
namespace mgx {
	class blo {
	public:
		struct element {
			unsigned int gl_type;
			unsigned int count;
			unsigned char normal;
		};
	private:
		std::vector<element> elements;
		unsigned int stride;

	public:

		inline blo() {
			stride = 0;
		}

		template<typename T>
		void AddAttrib(unsigned int count);

		inline std::vector<element> GetElements() const {return elements;}
		inline unsigned int GetStride() const {return stride;}

		void Compile() const;
	};
};