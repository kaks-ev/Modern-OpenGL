#ifndef WINDOW_H
#define WINDOW_H

#include "core.h"
#include "IO/keyListener.h"
#include "IO/mouseListener.h"


class Window
{
protected:
	GLFWwindow* m_Window;
private:
	unsigned int m_Width;
	unsigned int m_Height;

	const char* m_Title;

public:
	Window(const char* title);
	~Window();

	bool init();
	void render();
	void update();
	void callBacks();

	virtual void ImGuiInit();
	virtual void ImGuiRender();

	unsigned int getWidth() { return m_Width; }
	unsigned int getHeight() { return m_Height; }
	static void framebuffersizecallback(GLFWwindow* window, int width, int height);
	GLFWwindow* getWindow() { return m_Window; }

	bool loop();

};
#endif // WINDOW_H

