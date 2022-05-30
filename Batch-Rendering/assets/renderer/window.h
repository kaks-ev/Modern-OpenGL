#ifndef WINDOW_H
#define WINDOW_H

#include "core.h"
#include "IO/keyListener.h"
#include "IO/mouseListener.h"

class Window
{
private:
	GLFWwindow* m_Window;
	unsigned int m_Width;
	unsigned int m_Height;

	const char* m_Title;

	double deltaTime;
	double lastFrame;
	float currentTime;

public:
	Window(const char* title);
	~Window();

	bool init();
	void render();
	void update();
	void callBacks();

	void imGuiRender();

	unsigned int getWidth() { return m_Width; }
	unsigned int getHeight() { return m_Height; }
	static void framebuffersizecallback(GLFWwindow* window, int width, int height);

	bool loop();

};
#endif // WINDOW_H

