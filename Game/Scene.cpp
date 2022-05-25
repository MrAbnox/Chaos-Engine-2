#include "Scene.h"
#include "../Components/MeshRenderer.h"

Scene::Scene()
{
}

void Scene::load()
{
	//TODO: Read from file and pass string

	//TEMP
	createPrimitive(CUBE);
}

void Scene::start()
{
	for (size_t i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i].get()->initialize();
	}
}

void Scene::update()
{
	for (size_t i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i].get()->update();
	}

	for (int i = 0; i < sceneObjects.size(); i++) 
	{
		if (sceneObjects[i]->getShouldDestroy())
		{
			sceneObjects.erase(sceneObjects.begin() + i);
		}
	}
}

void Scene::render()
{
	for (size_t i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i].get()->render();
	}
}

void Scene::saveScene()
{
}

void Scene::unload()
{
}

void Scene::createEmpty()
{
}

void Scene::createPrimitive(Primitive primitive, glm::vec3& pos)
{

	
	GameObject prim;
	prim.addComponent<MeshRenderer>();
	switch (primitive)
	{
	case CUBE:

		
		break;
		
	case QUAD:

		
		break;
		
	default:
		break;
	}
	
	//sceneObjects.push_back(std::make_shared<prim>());
}

void Scene::duplicateObject()
{
}

void Scene::deleteObject()
{
}

//TODO: Make sure this doesn't create another copy in memory and just passes the reference
std::vector<std::shared_ptr<GameObject>> Scene::getSceneObjects()
{
	return sceneObjects;
}
