#ifndef TEXTURE_H
#define TEXTURE_H

#include "core.h"

class Texture {

private:
	unsigned int ID;
	unsigned char* m_data;
	std::string filePath;
	int m_Width, m_Height, m_NoChannels;

public:
	Texture();
	Texture(const std::string& path);
	~Texture();

	void Bind() const;
	void Unbind() const;
	unsigned int getID() { return ID; }

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};
#endif // !TEXTURE_H

