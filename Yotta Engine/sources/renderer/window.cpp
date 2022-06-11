#include "window.h"

#include "IO\mouseListener.h"
#include "renderer\icon.h"
#include "Utils\ImGuiLayer.h"

Window::Window(const char* title)
	: m_Window(0), title(title)
{
	Width = 1280;
	Height = Width * 9 / 16;
	bgcolor[3] = 1.0f;

	init();
}

Window::~Window()
{
	ImGuiLayer::Detach();
	glfwTerminate();
	glfwDestroyWindow(m_Window);
	std::cout << "WINDOW WAS CLOSED\n";
}

bool Window::init()
{
	// WINDOW CONFIGURATION
	if (!glfwInit()) {
		std::cout << "ERROR : FAILED TO INITIALIZE GLFW\n";
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	m_Window = glfwCreateWindow(Width, Height, title, nullptr, nullptr);
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
	Icon icon(m_Window, "assets/img/logo.jpg");

	callBacks();
	ImGuiLayer::Init(m_Window);
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSwapInterval(true);

	bgcolor[0] = 0.1f;
	bgcolor[1] = 0.1f;
	bgcolor[2] = 0.1f;
	bgcolor[3] = 1.0f;

	return true;
}

void Window::render() {
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(bgcolor[0] * bgcolor[3], bgcolor[1] * bgcolor[3], bgcolor[2] * bgcolor[3], bgcolor[3]);

	glfwGetFramebufferSize(m_Window, &Width, &Height);
	glViewport(0, 0, Width, Height);
	glfwGetWindowSize(m_Window, &Width, &Height);
	ImGuiLayer::Begin();

	ImGuiLayer::Settings();
	ImGuiLayer::Overlay();
}

void Window::update()
{
	ImGuiLayer::End();
	glfwSwapBuffers(m_Window);
}

void Window::callBacks()
{
	glfwSetFramebufferSizeCallback(m_Window, framebuffersizecallback);

	glfwSetKeyCallback(m_Window, Keyboard::keyCallBack);
	glfwSetCursorPosCallback(m_Window, Mouse::cursorPosCallback);
	glfwSetScrollCallback(m_Window, Mouse::mouseScrollCalback);
	glfwSetMouseButtonCallback(m_Window, Mouse::mouseButtonCallback);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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