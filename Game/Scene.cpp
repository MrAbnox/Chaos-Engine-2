#include "Scene.h"

Scene::Scene()
{
}

void Scene::start()
{
}

void Scene::update()
{
}

void Scene::render()
{
}

//TODO: Make sure this doesn't create another copy in memory and just passes the reference
std::vector<std::shared_ptr<GameObject>> Scene::getSceneObjects()
{
	return sceneObjects;
}
