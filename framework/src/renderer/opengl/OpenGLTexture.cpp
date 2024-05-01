//
// Created by Sterling on 2/8/2024.
//

#include <iostream>
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include <stb/stb_image.h>

namespace strl
{

OpenGLTexture::OpenGLTexture()
	: internal_format_(GL_RGBA), image_format_(GL_RGBA),
	  wrap_s_(GL_REPEAT), wrap_t_(GL_REPEAT),
	  filter_min_(GL_LINEAR), filter_max_(GL_LINEAR)
{
}

OpenGLTexture::OpenGLTexture(GLint internal_format,
	GLint image_format,
	GLint wrap_s,
	GLint wrap_t,
	GLint filter_min,
	GLint filter_max)
	: internal_format_(internal_format), image_format_(image_format),
	  wrap_s_(wrap_s), wrap_t_(wrap_t),
	  filter_min_(filter_min), filter_max_(filter_max)
{

}

unsigned int OpenGLTexture::get_id() const
{
	return id_;
}

bool OpenGLTexture::generate(const std::string& path)
{
	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max_);

	stbi_set_flip_vertically_on_load(true);
	int nr_channels;
	unsigned char* data = stbi_load(path.c_str(), &width_, &height_,
		&nr_channels, STBI_rgb_alpha);
	if (!data)
	{
		// TODO: logging stuff
		std::cout << "Failed to load texture: " << path << std::endl;
		return false;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	return true;
}

void OpenGLTexture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, id_);
}

int OpenGLTexture::get_width() const
{
	return width_;
}

int OpenGLTexture::get_height() const
{
	return height_;
}

} // strl