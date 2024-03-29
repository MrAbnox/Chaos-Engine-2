#include "Application.h"
#include "Window.h"
#include "Editor.h"
#include "UI.h"
#include "Renderer.h"

Application* Application::instance()
{
	static Application* app = new Application;
	return app;
}

void Application::start()
{
	isRunning = true;
}

void Application::run()
{
	Window::instance()->initialize();
	Editor::instance()->initialize();
	UI::instance()->initialize();
	Renderer::instance()->initialize();

	while (isRunning && !glfwWindowShouldClose(Window::instance()->getWindow()))
	{
		//Window::instance()->clear();

		Editor::instance()->run();
		UI::instance()->run();
		Renderer::instance()->run();

		Window::instance()->swapBuffers();
	}
}
