#ifndef WINDOW_H
#define WINDOW_H

#include "Origin\IO\Events\Event.h"

namespace Origin {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Origin Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	struct WindowData
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		std::function<void(Event&)> EventCallback;
	};

	class Window
	{
	private:
		GLFWwindow* m_Window;
		WindowData m_Data;

	public:
		float bgcolor[4];
		Window(const WindowProps& props);
		~Window();

		bool init(const WindowProps& props);
		void OnRender();
		void Run();

		bool loop();
		void SetEventCallback(const std::function<void(Event&)>& callback) 
		{ 
			m_Data.EventCallback = callback;
		};

		void OnUpdate();

		inline unsigned int GetWidth() { return m_Data.Width; };
		inline unsigned int GetHeight() { return m_Data.Height; };

		static Window* Create(const WindowProps& props = WindowProps());
		void WindowCallbacks();

		GLFWwindow* getWindow() { return m_Window; }
	};
}
#endif // WINDOW_H

