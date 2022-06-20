#ifndef APPLICATION_H
#define APPLICATION_H

#include "log.h"
#include "Origin\renderer\window.h"
#include "Origin\IO\Events\AppEvent.h"

namespace Origin {
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running;
	};

	Application* CreateApplication();
}

#endif // !APPLICATION_H