#include "window.h"

#include "IO\mouseListener.h"
#include "renderer\icon.h"
#include "Utils\ImGuiLayer.h"
#include "renderer\renderer.h"

Window::Window(const char* title)
	: m_Window(0), title(title)
{
	Width = 920;
	Height = Width * 9 / 16;

	// set default background color
	bgcolor[0] = 0.1f;
	bgcolor[1] = 0.1f;
	bgcolor[2] = 0.1f;
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

void Window::glfw_error_callback(int error, const char* description) {
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

bool Window::init()
{
	// WINDOW CONFIGURATION
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
		std::cout << "ERROR : FAILED TO INITIALIZE GLFW\n";
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	//glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

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

	ImGuiLayer::Init(m_Window);
	ImGuiLayer::Settings();
	callBacks();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSwapInterval(true);

	return true;
}

void Window::render() {
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(bgcolor[0] * bgcolor[3], bgcolor[1] * bgcolor[3], bgcolor[2] * bgcolor[3], bgcolor[3]);

	// ==== VERY IMPORTANT USE YOUR ACTUAL MONITOR RESOLUTION ====
	int Width = 1366;
	int Height = 720;
	glViewport(0, 0, Width, Height);
	glfwGetWindowSize(m_Window, &Width, &Height);

	ImGuiLayer::Begin();
}

void Window::update()
{
	ImGuiLayer::End();
	GLCall(glfwSwapBuffers(m_Window));
}

void Window::callBacks()
{
	glfwSetKeyCallback(m_Window, Keyboard::keyCallBack);
	glfwSetCursorPosCallback(m_Window, Mouse::cursorPosCallback);
	glfwSetScrollCallback(m_Window, Mouse::mouseScrollCalback);
	glfwSetMouseButtonCallback(m_Window, Mouse::mouseButtonCallback);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

bool Window::loop()
{
	if (Keyboard::key(GLFW_KEY_ESCAPE)) return false;
	return glfwWindowShouldClose(m_Window) == false;
}