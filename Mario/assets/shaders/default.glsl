//type vertex
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in float aTexIndex;

out vec3 fColor;
out vec2 fTexCoord;
out float v_TexIndex;

uniform mat4 projection;
uniform mat4 uView;

void main(){
	
	fColor = aColor;
	fTexCoord = aTexCoords;
	v_TexIndex = aTexIndex;

	gl_Position = projection * uView * vec4( aPos, 1.0f );
}

//type fragment
#version 460 core

out vec4 color;

in vec3 fColor;
in vec2 fTexCoord;
in float v_TexIndex;

uniform sampler2D uTexture[8];

void main(){

	int index = int(v_TexIndex);
	color = texture(uTexture[index], fTexCoord);
}