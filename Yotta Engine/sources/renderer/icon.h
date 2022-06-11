#ifndef ICON_H
#define ICON_H

#include "core.h"

class Icon
{
private:
	unsigned char* m_Data;
	int m_Width, m_Height, m_nChannels;
	std::string m_FilePath;
public:
	Icon(GLFWwindow* window, const std::string& path);

};

#endif