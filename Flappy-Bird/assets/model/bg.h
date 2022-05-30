#ifndef BG_H
#define BG_H

#include "renderer/mesh.h"
#include "core.h"

class background
{
private:
	Shader m_Shader;
	Texture m_Texture;

	Mesh BG;
public:

	background(const std::string& shaderFilepath, const std::string& textureFilepath);
	~background();

	void draw();
	void bind();
	void update();


};

#endif