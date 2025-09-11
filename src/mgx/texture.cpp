#include <mgx/texture.hpp>

namespace mgx {
	texture::texture() {
		this->id 				= 0;
		this->local_buffer 		= nullptr;
		this->width 			= 0;
		this->height 			= 0;
		this->bits_per_pixel 	= 0;
		GLCall( glGenTextures(1, &id) );
	}

	texture::texture(const std::string& file_path) {
		this->id 				= 0;
		this->local_buffer 		= nullptr;
		this->width 			= 0;
		this->height 			= 0;
		this->bits_per_pixel 	= 0;
		GLCall( glGenTextures(1, &id) );

		LoadFromFile(file_path);
	}

	texture::~texture() {
		Unbind();
		GLCall( glDeleteTextures(1, &id) );
	}

	void texture::LoadFromFile(const std::string& file_path) {
		Bind();

		GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
		GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
		GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
		GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );

		stbi_set_flip_vertically_on_load(1);
		this->local_buffer = stbi_load(file_path.c_str(), &width, &height, &bits_per_pixel, 4);

		GLCall( glTexImage2D (
			GL_TEXTURE_2D, 
			0, 
			GL_RGBA8, 
			this->width, 
			this->height, 
			0, 
			GL_RGBA, 
			GL_UNSIGNED_BYTE, 
			this->local_buffer
		));
		
		Unbind();

		if (local_buffer)
			stbi_image_free(local_buffer);
	}

	void texture::Bind(unsigned int slot) const {
		GLCall( glActiveTexture(GL_TEXTURE0 + slot) );
		GLCall( glBindTexture(GL_TEXTURE_2D, this->id) );
	}

	void texture::Unbind() const {
		GLCall( glBindTexture(GL_TEXTURE_2D, 0) );
	}
};