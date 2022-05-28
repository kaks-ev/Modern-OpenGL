#include "indexBuffer.h"
#include "renderer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
  : m_Count(count) {
	sizeof(unsigned int) == sizeof(GLuint);
  glGenBuffers(1, &m_RendererID); // 1 = active 0 = unactie
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
  glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}