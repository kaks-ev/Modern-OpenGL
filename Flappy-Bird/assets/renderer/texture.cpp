#include "Texture.h"

Texture::Texture(const std::string& path)
	: ID(0), filePath(path), m_Width(0), m_Height(0), m_data(nullptr)
{

	stbi_set_flip_vertically_on_load(true);

	// set the file path
	m_data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_NoChannels, 4);
	// generate texture
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	// set texture filter first
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// set texture wrap mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set channel mode

	if (m_data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
		glBindTexture(GL_TEXTURE_2D, 0);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else std::cout << "FAILED TO LOAD TEXTURE\n";
	stbi_image_free(m_data);
}

Texture::~Texture()
{
	Unbind();
	glDeleteTextures(1, &ID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
