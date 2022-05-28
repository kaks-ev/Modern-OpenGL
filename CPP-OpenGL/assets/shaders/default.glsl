//shader vertex
#version 460 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexture;
layout (location = 3) in vec3 vertexColor;

out vec3 vs_Position;
out vec3 vs_Color;
out vec2 vs_Texture;
out vec3 vs_Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vs_Position = vertexPosition;
    vs_Color = vertexColor;
    vs_Texture = vec2(vertexTexture.x, vertexTexture.y);
    vs_Normal = mat3(model) * vertexNormal;

    gl_Position = projection * view * model * vec4(vs_Position, 1.0f);
}

//shader fragment
#version 460 core

in vec3 vs_Color;
in vec2 vs_Texture;
in vec3 vs_Normal;
in vec3 vs_Position;

out vec4 color;

uniform sampler2D u_texture;
uniform vec3 lightPos0;

void main()
{
    color = texture(u_texture, vs_Texture);
}