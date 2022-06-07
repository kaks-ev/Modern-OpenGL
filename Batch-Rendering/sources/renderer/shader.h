#ifndef SHADER_H
#define SHADER_H
#include "core.h"

struct ShaderProgramSources{

  std::string VertexSources;
  std::string FragmentSources;
};

class Shader
{
private:
  std::string m_Filepath;
  unsigned int m_RendererID;
  std::unordered_map<std::string, int> m_UniformLocationCache;

public:
  Shader();
  Shader(const std::string &filepath);
  ~Shader();

  void Bind() const;
  void Unbind() const;

    // FLOAT UNIFORM
  void SetUniformFloat(const std::string& name, float v0);
  void SetUniformFloat(const std::string& name, float v0, float v1);
  void SetUniformFloat(const std::string& name, float v0, float v1, float v2);
  void SetUniformFloat(const std::string &name, float v0, float v1, float v2, float v3);

    // INT UNIFORM
  void SetUniformInt(const std::string &name, int v0);
  void SetUniformInt(const std::string &name, int v0, int v1);
  void SetUniformInt(const std::string &name, int v0, int v1, int v2);
  void SetUniformInt(const std::string &name, int v0, int v1, int v2, int v3);

  // INT VALUE
  void SetUniformiv(const std::string& name, GLsizei count, const GLint* v0);

  // MATRIX UNIFORM
  void SetUniformMatrix(const std::string &name, const glm::mat4 &mat4);

  // VECTOR UNIFORM
  void SetUniformVector(const std::string& name, const glm::vec3 &vec3);

private:
  ShaderProgramSources ParseShader(const std::string &filePath);
  unsigned int CompileShader(unsigned int type, const std::string &source);
  unsigned int createShader(const std::string &vertexShader, std::string &fragmentShader);
  int GetUniformLocation(const std::string &name);
};

#endif