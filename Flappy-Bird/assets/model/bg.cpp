#include "bg.h"

background::background(const std::string& shaderFilepath, const std::string& textureFilepath)
	: m_Shader(shaderFilepath), m_Texture(textureFilepath)
{
	m_Shader.Bind();
	m_Texture.Bind(0);
	m_Shader.SetUniformInt("uTexture", 0);

	float vertices[] =
	{
		// position					/ texture
		-16.0f, -10.0f, 0.2f, 0.0f, 0.0f,
			0.0f, -10.0f, 0.2f, 1.0f, 0.0f,
			0.0f,  10.0f, 0.2f, 1.0f, 1.0f,
		-16.0f,  10.0f, 0.2f, 0.0f, 1.0f
	};
	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	
	BG.init(vertices, indices, 20);

}

void background::draw()
{
	bind();
	BG.Draw();
}

void background::bind()
{
	m_Shader.Bind();
	m_Texture.Bind(0);
	m_Shader.SetUniformInt("uTexture", 0);

	BG.Bind();
}

void background::update()
{

}
