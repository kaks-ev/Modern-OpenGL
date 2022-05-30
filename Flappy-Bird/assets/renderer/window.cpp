#include "window.h"
#include "renderer/icon.h"

Window::Window(const char* title)
	: m_Window(0), m_Title(title)
{
	this->m_Width = 800;
	this->m_Height = this->m_Width * 10 / 16;

	init();
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	std::cout << "WINDOW WAS CLOSED\n";
}

bool Window::init()
{

	if (!glfwInit()) {
		std::cout << "ERROR : FAILED TO INITIALIZE GLFW\n";
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
	if (!m_Window) {
		std::cout << "ERROR : FAILED TO CREATE WINDOW\n";
		return false;
	}

	glfwMakeContextCurrent(m_Window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR : FAILED TO INITIALIZE GLEW\n";
		return false;
	}
	else {
		std::cout << "OPENGL VERSION : " << glGetString(GL_VERSION) << "\n";
		std::cout << "GLEW VERSION : " << glewGetString(GLEW_VERSION) << "\n\n";
	}
	std::cout << "PRESS ESCAPE TO CLOSE WINDOW\n";
	Icon icon(m_Window, "assets/img/icon.png");

	glfwSetFramebufferSizeCallback(m_Window, framebuffersizecallback);
	glfwSetKeyCallback(m_Window, Keyboard::keyCallBack);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSwapInterval(true);

	return true;
}

void Window::render()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	currentTime = (float)glfwGetTime();
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;
}

void Window::update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Window::framebuffersizecallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool Window::loop()
{
	if (Keyboard::key(GLFW_KEY_ESCAPE)) return false;
	return glfwWindowShouldClose(m_Window) == false;
}