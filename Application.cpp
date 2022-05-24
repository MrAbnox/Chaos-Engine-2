#include "Application.h"
#include "Window.h"
#include "EditorLayer.h"
#include "UI.h"

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
	EditorLayer::instance()->initialize();
	UI::instance()->initialize();

	while (isRunning && !glfwWindowShouldClose(Window::instance()->getWindow()))
	{
		Window::instance()->clear();

		//EditorLayer::instance()->run();
		//UI::instance()->run();

		Window::instance()->swapBuffers();
	}
}
