#include "core.h"
#include "renderer.h"


void Renderer::Clear() const
{
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // window colr
  glClear(GL_COLOR_BUFFER_BIT);
}
//void Renderer::DrawElements(const VertexArray &va, IndexBuffer &ib, const Shader &shader) const
//{
//  shader.Bind();
//  va.Bind();
//  ib.Bind();
//  glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
//}

//void Renderer::DrawArrays(const VertexArray &va, int count) const
//{
//  va.Bind();
//  glDrawArrays(GL_TRIANGLES, 0, count);
//}


void Renderer::wireframe() const
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
void Renderer::FILL() const
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}