#include "Origin\Application\Application.h"
extern Origin::Application* Origin::CreateApplication();
int main() {
	Origin::Log::Init();
	auto app = Origin::CreateApplication();
	app->Run();
	delete app;
}