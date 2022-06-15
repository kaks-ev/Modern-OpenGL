#include "mouseListener.h"
#include "core.h"

double Mouse::x = 0;
double Mouse::y = 0;
double Mouse::lastX = 0;
double Mouse::lastY = 0;
double Mouse::dx = 0;
double Mouse::dy = 0;
double Mouse::scrollDX = 0;
double Mouse::scrollDY = 0;
bool Mouse::firstMouse = false;
bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::buttonsChanged[GLFW_MOUSE_BUTTON_LAST] = { 0 };

void Mouse::cursorPosCallback(GLFWwindow* window, double _x, double _y)
{
	ImGui_ImplGlfw_CursorPosCallback(window, _x, _y);
	x = _x;
	y = _y;
	if (firstMouse) {
		lastX = x;
		lastY = y;
		firstMouse = false;
	}
	dx = x - lastX;
	dy = lastY - y; // inverted

	lastX = x;
	lastY = y;
}
void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

	if (action != GLFW_RELEASE)
	{
		if (!buttons[button]) {
			
			buttons[button] = true;
		}

		else {
			buttons[button] = false;
			return;
		}

		buttonsChanged[button] = action != GLFW_REPEAT;
	}
}
void Mouse::mouseScrollCalback(GLFWwindow* window, double dx, double dy) {

	ImGui_ImplGlfw_ScrollCallback(window, dx, dy);

	scrollDX = dx;
	scrollDY = dy;
}
double Mouse::getMouseX() { return x; }
double Mouse::getMouseY() { return y; }
double Mouse::getDX() {
	double _dx = dx;
	dx = 0;
	return dx;
}
double Mouse::getDY() {
	double _dy = dy;
	dy = 0;
	return dy;
}
double Mouse::getScrollDX() {
	double dx = scrollDX;
	scrollDX = 0;
	return dx;
}
double Mouse::getScrollDY() {
	double dy = scrollDY;
	scrollDY = 0;
	return dy;
}

bool Mouse::button(int button) { return buttons[button]; }
bool Mouse::buttonChanged(int button) {
	bool ret = buttonsChanged[button];
	buttonsChanged[button] = false;
	return ret;
}
bool Mouse::buttonWentUp(int button) { return !buttons[button] && buttonChanged(button); }
bool Mouse::buttonWentDown(int button) { return buttons[button] && buttonChanged(button); }