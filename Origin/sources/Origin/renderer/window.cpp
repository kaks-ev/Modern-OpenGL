#include "window.h"

#include "Origin\renderer\icon.h"
#include "Origin\Utils\ImGuiLayer.h"
#include "log.h"

#include "Origin\IO\Events\KeyEvent.h"
#include "Origin\IO\Events\MouseEvent.h"
#include "Origin\IO\Events\AppEvent.h"

namespace Origin {

	Window* Window::Create(const WindowProps& props) {
		return new Window(props);
	}

	Window::Window(const WindowProps& props)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;

		// set default background color
		bgcolor[0] = 0.1f;
		bgcolor[1] = 0.1f;
		bgcolor[2] = 0.1f;
		bgcolor[3] = 1.0f;

		init(props);
	}

	Window::~Window()
	{
		Utils::ImGuiLayer::Detach();
		glfwTerminate();
		glfwDestroyWindow(m_Window);
	}

	bool Window::init(const WindowProps& props)
	{
		// WINDOW CONFIGURATION
		if (!glfwInit()) {
			ORG_CORE_ERROR("ERROR :FAILED TO INITIALIZE GLFW");
			return false;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		//glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

		m_Window = glfwCreateWindow((int)m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		if (!m_Window) {
			ORG_CORE_ERROR("ERROR : FAILED TO CREATE WINDOW");
			glfwTerminate();
			return false;
		}
		Icon icon(m_Window, "assets/img/logo.jpg");

		ORG_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		glfwMakeContextCurrent(m_Window);

		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			ORG_CORE_ERROR("ERROR : FAILED TO INITIALIZE GLEW");
			glfwTerminate();
			return false;
		}
		
		WindowCallbacks();

		Utils::ImGuiLayer::Init(m_Window);
		Utils::ImGuiLayer::Settings();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glfwSwapInterval(true);
		return true;
	}

	void Window::WindowCallbacks()
	{
		// Set init window user pointer first
		glfwSetWindowUserPointer(m_Window, &m_Data);

		// set window callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent e(width, height);
				data.EventCallback(e);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent e;
				data.EventCallback(e);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent e(key, 0);
						data.EventCallback(e);
						break;
					};
					case GLFW_RELEASE:
					{
						KeyReleasedEvent e(key);
						data.EventCallback(e);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent e(key, 1);
						data.EventCallback(e);
						break;
					}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent e(button);
						data.EventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent e(button);
						data.EventCallback(e);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent e((float)xOffset, (float)yOffset);
				data.EventCallback(e);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent e((float)xPos, (float)yPos);
				data.EventCallback(e);
			});
	}

	void Window::OnRender() {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(bgcolor[0] * bgcolor[3], bgcolor[1] * bgcolor[3], bgcolor[2] * bgcolor[3], bgcolor[3]);

		// ==== VERY IMPORTANT USE YOUR ACTUAL MONITOR RESOLUTION ====
		int Width = 1366;
		int Height = 720;
		glViewport(0, 0, Width, Height);
		//glfwGetWindowSize(m_Window, &Width, &Height);

		Utils::ImGuiLayer::Begin();
	}

	void Window::OnUpdate()
	{
		Utils::ImGuiLayer::End();
		glfwSwapBuffers(m_Window);
	}

	void Window::Run() {
		OnRender();
		OnUpdate();
	}

	bool Window::loop()
	{
		return glfwWindowShouldClose(m_Window) == false;
	}
}