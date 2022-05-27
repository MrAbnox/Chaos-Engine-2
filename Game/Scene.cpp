#include "Scene.h"
#include "../Components/MeshRenderer.h"
#include "../Application/Renderer.h"

Scene::Scene()
{
}

void Scene::load()
{
	Renderer::instance();
	//TODO: Read from file and pass string
	GameObject obj = Renderer::instance()->getObject("Camera");
	addObjectToScene(obj);

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

void Scene::createPrimitive(Prim primitive, glm::vec3& pos)
{
	GameObject prim;
	
	switch (primitive)
	{
	case CUBE:

		prim = Renderer::instance()->getObject("Cube");
		break;
		
	case QUAD:

		
		break;
		
	default:
		break;
	}

	addObjectToScene(prim);
}

void Scene::duplicateObject()
{
}

void Scene::deleteObject()
{
}

void Scene::addObjectToScene(GameObject& object)
{
	sceneObjects.push_back(std::make_shared<GameObject>(object));
}

//TODO: Make sure this doesn't create another copy in memory and just passes the reference
std::vector<std::shared_ptr<GameObject>> Scene::getSceneObjects()
{
	return sceneObjects;
}
