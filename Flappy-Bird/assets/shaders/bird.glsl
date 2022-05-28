//type vertex
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;

out vec2 v_Texture;
float size = 1.5f;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(size * aPos, 1.0f);
	v_Texture = aTexture;
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
	//if(Color.w < 1.0) discard;
}