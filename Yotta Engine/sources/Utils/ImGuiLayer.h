#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "core.h"
#include "renderer/window.h"

namespace ImGuiLayer {

	void Init(GLFWwindow* window);
	void ImGui_ImplGlfw_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void Settings();
	void Overlay();
	void Begin();
	void End();
	void Detach();
}

#endif // !IMGUILAYER_H