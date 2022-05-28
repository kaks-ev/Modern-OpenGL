#include "core.h"

// LIBS
#include "shader.h"
#include "texture.h"
#include "mouse.h"
#include "keyboard.h"
#include "camera.h"

const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = SCREEN_HEIGHT * 16 / 9;
const char* title = "OpenGL";
GLFWwindow* window;
glm::mat4 mouseTransform = glm::mat4(1.0f);

Keyboard keyboard;

void procInput(GLFWwindow* window){
	if(keyboard.key(GLFW_KEY_ESCAPE)){
		glfwSetWindowShouldClose(window, true);
		std::cout << "WINDOW WAS CLOSED\n";
	}
}

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
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	int display_w, display_h;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glfwSetKeyCallback(window, Keyboard::keyCallBack);
	glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
	glfwSetScrollCallback(window, Mouse::mouseWheelCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// ===================== CUBE =====================
	float vertices[] = {
    // position                 normal              texcoord
    -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    0.0f, 0.0f, // 0 [FRONT] bottom left
     0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    1.0f, 0.0f, // 1 [FRONT] bottom right
     0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    1.0f, 1.0f, // 2 [FRONT] top right
    -0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    0.0f, 1.0f,	// 3 [FRONT] top left

    -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f, // 4 [BACK] bottom left
     0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f, // 5 [BACK] bottom right
     0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f, // 6 [BACK] top right
    -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f, // 7 [BACK] top left

    -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f, // 8 [LEFT] top left	
    -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f, // 9 [LEFT] top right
    -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f, //10 [LEFT] bottom right
    -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f, //11 [LEFT] bottom left

     0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f, //12 [RIGHT] top left	
     0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f, //13 [RIGHT] top right
     0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f, //14 [RIGHT] bottom right
     0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f, //15 [RIGHT] bottom left

		-0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    1.0f, 0.0f, //16 [TOP] top left
     0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    1.0f, 1.0f, //17 [TOP] top right
     0.5f,  0.5f, -0.5f,     0.0f,  0.0f,  1.0f,    0.0f, 1.0f, //18 [TOP] bottom right
    -0.5f,  0.5f, -0.5f,     0.0f,  0.0f,  1.0f,    0.0f, 0.0f,	//19 [TOP] bottom left
		
		-0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    1.0f, 0.0f, //20 [BOTTOM] top left
     0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    1.0f, 1.0f, //21 [BOTTOM] top right
     0.5f, -0.5f, -0.5f,     0.0f,  0.0f,  1.0f,    0.0f, 1.0f, //22 [BOTTOM] bottom right
    -0.5f, -0.5f, -0.5f,     0.0f,  0.0f,  1.0f,    0.0f, 0.0f,	//23 [BOTTOM] bottom left

  };

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	unsigned int va, vb,  ib;

	glGenVertexArrays(1, &va);
	glBindVertexArray(va);
	
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices , GL_STATIC_DRAW);
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	// normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// ===================== MATH =====================
	glm::vec3 position(0.0f);
	glm::vec3 rotation(0.0f);
	glm::vec3 scale(1.0f);

	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(3.0f);

	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // x
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // y
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // z
	model = glm::scale(model, scale);

	glm::vec3 cameraPos(0.0f, 0.0f, 2.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, worldUp);

	float fov = 90.0f;
	float nearPlane = 0.1f, farPlane = 1000.0f;

	projection = glm::perspective(glm::radians(fov), 
	(float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, nearPlane, farPlane);


	// ===================== SHADER =====================
	Shader shader0("assets/shaders/default.glsl");
	shader0.Bind();
	shader0.SetUniformMat4fv("model", model);
	shader0.SetUniformMat4fv("view", view);
	shader0.SetUniformMat4fv("projection", projection);

	// ===================== TEXTURE =====================
	Texture cubeTexture("assets/img/brick.png");
	cubeTexture.Bind();


	// ===================== IMGUI =====================
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	bool drawCube = true;
	bool drawFloor = false;
	bool wireframe = false;

	ImVec4 clear_color = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);

	// MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		shader0.Bind();
		cubeTexture.Bind();

		procInput(window);

		// ===================== IMGUI =====================
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("settings");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("PRESS ESCAPE TO CLOSE WINDOW");
		ImGui::Checkbox("Draw Cube", &drawCube); ImGui::SameLine(); ImGui::Checkbox("Show Cube Wireframe", &wireframe);
		ImGui::ColorEdit3("BG Color", (float *)&clear_color);
		ImGui::End();

		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// =============== TRANSFORMATION ===============
		model = glm::translate(model, position);
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // x
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // y
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // z
		model = glm::scale(model, scale);

		glm::vec3 cameraPos(0.0f, 0.0f, 2.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, worldUp);

		float fov = 90.0f;
		float nearPlane = 0.1f, farPlane = 1000.0f;

		projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, nearPlane, farPlane);

		shader0.SetUniformMat4fv("model", model);
		shader0.SetUniformMat4fv("view", view);
		shader0.SetUniformMat4fv("projection", projection);

		// DRAW CUBE
		if(drawCube)
		{
			glBindVertexArray(va);

			// WIREFRAM MODE
			if(wireframe){
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				cubeTexture.Unbind();
			}
			if(!wireframe){
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				cubeTexture.Bind();
			}
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glDeleteVertexArrays(1, &va);
	glDeleteBuffers(1, &vb);
	glDeleteBuffers(1, &ib);
	
	glfwDestroyWindow(window);
	return 0;
}