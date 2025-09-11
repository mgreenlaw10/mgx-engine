#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include <STB/stb_image.h>

#include <error.hpp>

#include <string>


namespace mgx {
	class texture {
	private:
		unsigned int id;

		unsigned char* local_buffer;

		int width;
		int height;
		int bits_per_pixel;
	public:
		texture();
		texture(const std::string& file_path);
		~texture();

		void LoadFromFile(const std::string& file_path);

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline unsigned int GetWidth() const {return width;}
		inline unsigned int GetHeight() const {return height;}
		inline unsigned int GetBPP() const {return bits_per_pixel;}
	};
};