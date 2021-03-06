#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "renderer/renderer.h"

class IndexBuffer
{
private:
  unsigned int m_RendererID;
  unsigned int m_Count;
public:
  IndexBuffer();
  IndexBuffer(const unsigned int *data, unsigned int count);
  ~IndexBuffer();

  void Bind() const;
  void Unbind() const;

  inline const unsigned int GetCount() const {return m_Count;}
};

#endif // INDEXBUFFER_H