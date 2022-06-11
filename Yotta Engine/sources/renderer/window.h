#ifndef WINDOW_H
#define WINDOW_H

#include "core.h"
#include "IO/Camera.h"
#include "IO/mouseListener.h"
#include "IO/keyListener.h"

class Window
{
private:
	GLFWwindow* m_Window;
public:
	const char* title;
	int Width;
	int Height;
	float bgcolor[4];

	Window();
	Window(const char* title);
	~Window();

	bool init();

	void update();
	void render();

	void callBacks();

	static void framebuffersizecallback(GLFWwindow* window, int width, int height);
	GLFWwindow* getWindow() { return m_Window; }
	bool loop();
};
#endif // WINDOW_H

