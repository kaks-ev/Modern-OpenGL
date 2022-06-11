#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "core.h"
#include "renderer/window.h"

namespace ImGuiLayer {

	void Init(GLFWwindow* window);
	void Settings();
	void Overlay();
	void Begin();
	void End();
	void Detach();
}

#endif // !IMGUILAYER_H