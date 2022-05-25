#include "Renderer.h"

Renderer* Renderer::instance()
{
	static Renderer* renderer = new Renderer;
	return renderer;
}

void Renderer::initialize()
{
	//TODO: Maybe load all scenes into memory
	
}

void Renderer::run()
{
	update();
	render();
}

void Renderer::update()
{
	for (size_t i = 0; i < currentScene->getSceneObjects().size(); i++)
	{
		if (currentScene->getSceneObjects()[i].get()->getIsEnabled())
		{
			currentScene->getSceneObjects()[i].get()->update();
		}
	}
}

void Renderer::render()
{
	for (size_t i = 0; i < currentScene->getSceneObjects().size(); i++)
	{
		if (currentScene->getSceneObjects()[i].get()->getIsEnabled())
		{
			currentScene->getSceneObjects()[i].get()->draw();
		}
	}	
}

void Renderer::loadScene()
{
}
