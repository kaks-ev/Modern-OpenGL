#include "Application.h"

namespace Origin {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	Application::~Application(){}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		ORG_CORE_TRACE("{0}", e);
	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);

		while (m_Window->loop()) { m_Window->Run(); }
		//while(true) {}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}

Origin::Application* Origin::CreateApplication() { return new Application; }