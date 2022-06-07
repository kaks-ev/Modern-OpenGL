#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "renderer/renderer.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int type);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};
#endif // VERTEXBUFFER_H