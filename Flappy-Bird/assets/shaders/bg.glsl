//type vertex
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextures;

out vec2 v_Texture;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * vec4(aPos, 1.0f);
	v_Texture = aTextures;
}

//type fragment
#version 460 core

in vec2 v_Texture;
out vec4 Color;

uniform sampler2D uTexture;

void main()
{
	vec4 tex1 = texture(uTexture, v_Texture);
	Color = tex1;
}