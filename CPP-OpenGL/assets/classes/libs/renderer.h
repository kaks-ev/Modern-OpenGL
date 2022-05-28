#ifndef RENDERER_H
#define RENDERER_H

#include "core.h"
#include "shader.h"

class Renderer
{
public:
  void Clear() const;
  //void DrawElements(const VertexArray &va, IndexBuffer &ib, const Shader &shader) const;
  //void DrawArrays(const VertexArray &va, int count) const;
  void wireframe() const;
  void FILL() const;
};

#endif