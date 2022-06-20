#ifndef DEARIMGUI_H
#define DEARIMGUI_H

#include "core.h"

namespace Origin
{
	namespace Utils
	{
		class DearImGui
		{
		private:

		public:

			void Init(GLFWwindow* window);
			void ImGui_ImplGlfw_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

			void Settings();
			void Overlay();
			void Begin();
			void End();
			void Detach();

		};
	}
}

#endif // !DEARIMGUI_H