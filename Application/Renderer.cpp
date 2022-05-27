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
	loadScene();
	loadGameObjects();
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
	//TODO: Remove this, it's temporary
	currentScene = new Scene();
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
	std::shared_ptr<MeshRenderer> temp = prim1->addComponent<MeshRenderer>();

	Mesh* mesh = new Primitive();
	mesh->setup();
	temp->setMaterial(*loadedMaterials["Default"]);
	temp->setMesh(*mesh);
	loadedGameObjects["Cube"] = prim1;

	GameObject* cam = new GameObject();
	cam->addComponent<Camera>();
	loadedGameObjects["Camera"] = cam;
}

GameObject Renderer::getObject(std::string name)
{
	return *loadedGameObjects[name];
}

Shader Renderer::getShader(std::string name)
{
	return *loadedShaders[name];
}
