//#include "pipe.h"
//
//Pipe::Pipe(std::string shaderPath, std::string texturePath)
//	: m_shaderPath(shaderPath), m_texturePath(texturePath)
//{
//	shader = Shader(shaderPath);
//	shader.Bind();
//	texture = Texture(texturePath);
//	texture.Bind(0);
//	shader.SetUniformInt("uTexture", 0);
//
//	float pipeVertices[] = {
//		// position					/ texture
//		-0.9f, -10.0f, 0.0f, 0.0f, 0.0f,
//		 0.9f, -10.0f, 0.0f, 1.0f, 0.0f,
//		 0.9f, -3.0f,  0.0f, 1.0f, 1.0f,
//		-0.9f, -3.0f,  0.0f, 0.0f, 1.0f
//	};
//	unsigned int pipeIndices[] = {
//		0, 1, 2,
//		2, 3, 0
//	};
//	VertexBuffer vb(pipeVertices, 20 * sizeof(float));
//	VertexBufferLayout layout;
//	layout.Push<float>(3);
//	layout.Push<float>(2);
//	vao.AddBuffer(vb, layout);
//	ebo = IndexBuffer(pipeIndices, 6);
//}
//
//Pipe::~Pipe()
//{
//
//}
//
//void Pipe::Draw()
//{
//	
//	glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, 0);
//}
//
//void Pipe::Update()
//{
//
//}
//
//void Pipe::Render()
//{
//	vao.Bind();
//	ebo.Bind();
//}
