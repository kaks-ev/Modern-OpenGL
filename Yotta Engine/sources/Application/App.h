#ifndef APP_H
#define APP_H

#include "renderer\window.h"
#include "renderer\shader.h"
#include "renderer\texture.h"
#include "IO/Camera.h"
#include "Utils/ImGuiLayer.h"

class App
{
public:

	Window window = Window("Yotta Engine");
	Shader shader = Shader("assets/shaders/default.glsl");
	Texture texture = Texture("assets/img/plane.jpg");

	void onStart();
	void update();

	void run();

	void ImGuiOnAttach();
	void CameraControl();
};

#endif // !APP_H