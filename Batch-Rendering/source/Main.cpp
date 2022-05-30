#include "renderer/window.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "IO/keyListener.h"
#include "IO/Camera.h"
#include "imgui/imgui.h"

Window Game("OpenGL Engine");
Keyboard keyboard;

int main() {

	Shader shader("assets/shaders/default.glsl");
	shader.Bind();

	Texture texture1("assets/img/logo.png");
	Texture texture2("assets/img/logo-invert.png");

	GLint samplers[2] = { 0, 1 };
	shader.SetUniformiv("uTexture", 2, samplers);

	float vertices[] = {
		//aPos						 aColor						 texCoords	 texID
		-1.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// 0
		-0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// 1
		-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,// 2
		-1.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,// 3

		 0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// 4
		 1.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,// 5
		 1.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,// 6
		 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,// 7
	};
	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};

	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// aPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	// aColor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// aTexID
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// aTexID
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

	shader.SetUniformMatrix("projection", glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	while (Game.loop()) {
		Game.render();

		shader.Bind();
		glBindTextureUnit(0, texture1.getID());
		glBindTextureUnit(1, texture2.getID());

		glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		shader.Unbind();

		Game.update();
	}

	return 0;
}