#include "shader.h"
#include "renderer.h"

Shader::Shader(const std::string &filepath)
    : m_Filepath(filepath), m_RendererID(0)
{
  ShaderProgramSources source = ParseShader(filepath);
  m_RendererID = createShader(source.VertexSources, source.FragmentSources);
  std::cout << "Vertex\n" << source.VertexSources << std::endl;
  std::cout << "Fragment\n" << source.FragmentSources << std::endl;
}

Shader::~Shader()
{
  glDeleteProgram(m_RendererID);
}

ShaderProgramSources Shader::ParseShader(const std::string &filePath)
{
  std::ifstream stream(filePath);

  enum class shaderType
  {
    NONE = -1,
    VERTEX,
    FRAGMENT
  };

  std::string line;
  std::stringstream ss[2];
  shaderType type = shaderType::NONE;

  while (getline(stream, line))
  {

    if (line.find("//shader") != std::string::npos)
    {
      if (line.find("vertex") != std::string::npos)
      {
        type = shaderType::VERTEX;
      }
      else if (line.find("fragment") != std::string::npos)
      {
        type = shaderType::FRAGMENT;
      }
    }
    else
    {
      ss[(int)type] << line << "\n";
    }
  }
  return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{
  unsigned int id = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int success;
  char infoLog[512];
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(id, 512, NULL, infoLog);
    std::cout << infoLog << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;

    glDeleteShader(id);
    return 0;
  }
  return id;
}

unsigned int Shader::createShader(const std::string &vertexShader, std::string &fragmentShader)
{
  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

void Shader::Bind() const
{
  glUseProgram(m_RendererID);
}
void Shader::Unbind() const
{
  glUseProgram(0);
}

// FLOAT UNIFORM
void Shader::SetUniform1f(const std::string &name, float v0){
  glUniform1f(GetUniformLocation(name), v0);
}
void Shader::SetUniform2f(const std::string &name, float v0, float v1){
  glUniform2f(GetUniformLocation(name), v0, v1);
}
void Shader::SetUniform3f(const std::string &name, float v0, float v1, float v2){
  glUniform3f(GetUniformLocation(name), v0, v1, v2);
}
void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3){
  glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}
// INT UNIFORM
void Shader::SetUniform1i(const std::string &name, int v0){
  glUniform1i(GetUniformLocation(name), v0);
}

void Shader::SetUniform2i(const std::string &name, int v0, int v1){
  glUniform2i(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3i(const std::string &name, int v0, int v1, int v2){
  glUniform3i(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4i(const std::string &name, int v0, int v1, int v2, int v3){
  glUniform4i(GetUniformLocation(name), v0, v1, v2, v3);
}

// MATRIX UNIFROM
void Shader::SetUniformMat4fv(const std::string &name, const glm::mat4 &mat4)
{
  glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat4));
}

// VECTOR UNIFORM
void Shader::SetUniform3fv(const std::string& name, const glm::vec3 &vec3)
{
  glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vec3));
}

int Shader::GetUniformLocation(const std::string &name)
{
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    return m_UniformLocationCache[name];

  int location = glGetUniformLocation(m_RendererID, name.c_str());
  if (location == -1)
    std::cout << "WARNING: UNIFORM '" << name << "' DOESN'T EXIST!!" << std::endl;

  m_UniformLocationCache[name] = location;
  return location;
}