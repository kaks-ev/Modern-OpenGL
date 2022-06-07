#include "window.h"
#include "renderer/icon.h"

Window::Window(const char* title)
	: m_Window(0), m_Title(title)
{
	this->m_Width = 1080;
	this->m_Height = this->m_Width * 9 / 16;

	init();
}

Window::~Window()
{
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

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
	Icon icon(m_Window, "assets/img/logo.jpg");
	callBacks();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSwapInterval(true);

	ImGuiInit();

	return true;
}

void Window::render()
{
	int display_w, display_h;
	glfwGetFramebufferSize(m_Window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glClearColor(bgcolor[0], bgcolor[1], bgcolor[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Window::callBacks()
{
	glfwSetFramebufferSizeCallback(m_Window, framebuffersizecallback);
	glfwSetKeyCallback(m_Window, Keyboard::keyCallBack);
	glfwSetCursorPosCallback(m_Window, Mouse::cursorPosCallback);
	glfwSetScrollCallback(m_Window, Mouse::mouseWheelCallback);
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

void Window::ImGuiInit()
{
	// IMGUI INITIALIZING
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& IO = ImGui::GetIO();
	(void)IO;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void Window::ImGuiRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void Window::ImGuiNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

