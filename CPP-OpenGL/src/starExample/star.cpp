#include "core.h"
#include "shader.h"
#include "window.h"
#include "input.h"
#include "callback.h"
#include "texture.h"

int main(){

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title, NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}
	glfwSetFramebufferSizeCallback(window, viewPort);

	Shader ourShader("./shaders/basic.glsl");

	// create triangle coordinate
	float vertices[] = {
		// STAR
		// position  			 / color
		-0.3f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, // 0
		 0.3f, 0.2f, 0.0f, 0.0f, 1.0f, 0.0f, // 1
		 0.0f, 0.8f, 0.0f, 0.0f, 0.0f, 1.0f, // 2

		 0.4f,-0.15f,0.0f, 1.0f, 0.0f, 0.5f, // 3
		-0.4f,-0.15f,0.0f, 0.0f, 0.5f, 0.0f, // 4

		 0.8f, 0.2f, 0.0f,  1.0f, 0.0f, 0.5f, // 5
		-0.8f, 0.2f, 0.0f,  0.0f, 0.5f, 0.0f, // 6
		
		 0.6f, -0.8f, 0.0f, 0.0f, 0.0f, 1.5f, // 7
		-0.6f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, // 8

		// CUBE
		// position  			 / color
		-0.8f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, // 9
		-0.4f, 0.4f, 0.0f, 0.0f, 1.0f, 0.0f, // 10
		-0.4f, 0.8f, 0.0f, 0.0f, 0.0f, 1.0f, // 11
		-0.8f, 0.8f, 0.0f, 0.5f, 1.0f, 0.0f, // 12

		 0.8f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, // 13
		 0.4f, 0.4f, 0.0f, 0.0f, 1.0f, 0.0f, // 14
		 0.4f, 0.8f, 0.0f, 0.0f, 0.0f, 1.0f, // 15
		 0.8f, 0.8f, 0.0f, 0.5f, 1.0f, 0.0f, // 16


	};
	unsigned int indices[]{
			// STAR
			0, 1, 2,
			0, 1, 3,
			3, 4, 0,
			0, 6, 4,
			0, 5, 3,
			4, 8, 3,
			3, 7, 4,

			// CUBE
			9, 10,11,
		 11, 12, 9,
		 13, 14,15,
		 15, 16,13,
		 
	};

	// create Vertex Array & Vertex Buffer
	unsigned int va, vb, ib;
	// gen vertex
	glGenVertexArrays(1, &va);
	glGenBuffers(1, &vb);
	glGenBuffers(1, &ib);

	// bind vertex
	glBindVertexArray(va);

	// get buffer data
	// vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices , GL_STATIC_DRAW);
	// index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * 2 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
  // color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * 2 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		userInput(window);
		consoleLog();

		//bind

		ourShader.Bind();
		glBindVertexArray(va);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);

		// draw
		glDrawElements(GL_TRIANGLES, 3 * 11, GL_UNSIGNED_INT, nullptr);

		// unbind
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &va);
	glDeleteBuffers(1, &vb);
	glDeleteBuffers(1, &ib);

	glfwTerminate();
	return 0;
}