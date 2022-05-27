#include "Renderer.h"
#include "../Components/MeshRenderer.h"
#include "../Editor/Camera.h"

Renderer* Renderer::instance()
{
	static Renderer* renderer = new Renderer;
	return renderer;
}

void Renderer::initialize()
{
	//Load all shaders
	loadShaders();
	loadMaterials();
	//Load all Materials into memory

	//TODO: Maybe load all scenes into memory
	loadGameObjects();
	loadScene();
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
	//if(!isLoadingScene)
	currentScene->render();
}

void Renderer::loadScene()
{
	//TODO: Remove this, it's temporary
	currentScene = new Scene();
	currentScene->start();
	currentScene->load();
}

void Renderer::loadShaders()
{
	Shader* temp = new Shader("shaders/default.vert", "shaders/default.frag");
	loadedShaders["Default"] = temp;
}

void Renderer::loadMaterials()
{
	//TODO: Read from file
	Material* mat = new Material();
	loadedMaterials["Default"] = mat;
}

void Renderer::loadGameObjects()
{
	//TODO: Do the same for plane gameobject
	GameObject* prim1 = new GameObject();
	loadedGameObjects["Cube"] = prim1;
	std::shared_ptr<MeshRenderer> temp = loadedGameObjects["Cube"]->addComponent<MeshRenderer>();

	Mesh* mesh = new Primitive();
	mesh->setup();
	temp->setMaterial(*loadedMaterials["Default"]);
	temp->setMesh(*mesh);

	GameObject* cam = new GameObject();
	loadedGameObjects["Camera"] = cam;
	loadedGameObjects["Camera"]->addComponent<Camera>();
}

GameObject Renderer::getObject(std::string name)
{
	return *loadedGameObjects[name];
}

Shader Renderer::getShader(std::string name)
{
	return *loadedShaders[name];
}
