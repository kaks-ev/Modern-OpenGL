//shader vertex
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vs_Position;
out vec3 vs_Color;
uniform mat4 ViewMatrix;

void main()
{ 
  vs_Position = aPos;
  vs_Color = aColor;
  gl_Position = ViewMatrix * vec4(vs_Position, 1.0f);

}

//shader fragment
#version 460 core

in vec3 vs_Color;
out vec4 fragColor;

void main()
{
  fragColor = vec4(vs_Color, 1.0f);
}