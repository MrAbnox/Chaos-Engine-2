#include "Renderer.h"

Renderer* Renderer::instance()
{
	static Renderer* renderer = new Renderer;
	return renderer;
}

void Renderer::initialize()
{
	//Load all shaders
	
	//Load all Materials into memory

	//TODO: Maybe load all scenes into memory

	//TODO: Remove this, it's temporary
	currentScene = new Scene();	
}

void Renderer::run()
{
	update();
	render();
}

void Renderer::update()
{
	if(!isLoadingScene)
		currentScene->update();
	
}

void Renderer::render()
{
	if(!isLoadingScene)
		currentScene->render();
}

void Renderer::loadScene()
{
}
