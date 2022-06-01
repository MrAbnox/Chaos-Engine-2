#include "Renderer.h"
#include "../Components/MeshRenderer.h"
#include "../Editor/Camera.h"
#include "../Game/Model.h"

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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
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
	std::shared_ptr<Shader> temp = std::make_shared<Shader>("shaders/default.vert", "shaders/default.frag");
	loadedShaders["Default"] = temp;

	std::shared_ptr<Shader> temp2 = std::make_shared<Shader>("shaders/skybox.vert", "shaders/skybox.frag");
	loadedShaders["Skybox"] = temp2;
}

void Renderer::loadMaterials()
{
	//TODO: Read from file
	std::shared_ptr<Material> mat = std::make_shared<Material>(SKYBOX);
	mat->setShader(loadedShaders["Skybox"]);
	loadedMaterials["Skybox"] = mat;
	loadedMaterials["Skybox"]->setShader(loadedShaders["Skybox"]);
}

void Renderer::loadGameObjects()
{
	//TODO: Automate this system with a prefab system (File reading)
	
	// Cube
	//________________________________________________________________________________
	std::shared_ptr<GameObject> obj1 = std::make_shared<GameObject>();
	std::shared_ptr<MeshRenderer> temp = obj1->addComponent<MeshRenderer>();
	loadedGameObjects["Cube"] = obj1;
	Mesh* mesh = new Primitive();
	mesh->setup();
	temp->setMaterial(loadedMaterials["Skybox"].get());
	temp->setMesh(mesh);

	// Floor
	//________________________________________________________________________________
	std::shared_ptr<GameObject> obj2 = std::make_shared<GameObject>();
	Mesh* model = new Model();
	std::dynamic_pointer_cast<Model>(model)->Create("Default");
	model->loadModel("floor/floor.obj");
	std::shared_ptr<GameObject> floor = std::make_shared<GameObject>();
	std::shared_ptr<MeshRenderer> temp2 = obj2->addComponent<MeshRenderer>();
	loadedGameObjects["Floor"] = obj2;
	mesh = model;
	mesh->setup();
	temp->setMaterial(loadedMaterials["Skybox"].get());
	temp->setMesh(mesh);

	// Camera
	//________________________________________________________________________________
	std::shared_ptr<GameObject> obj3 = std::make_shared<GameObject>();
	std::shared_ptr<GameObject> cam = std::make_shared<GameObject>();
	cam->addComponent<Camera>();
	loadedGameObjects["Camera"] = cam;
}

std::shared_ptr<GameObject> Renderer::getObject(std::string name)
{
	return loadedGameObjects[name];
}

Shader Renderer::getShader(std::string name)
{
	return *loadedShaders[name];
}

std::shared_ptr<GameObject> Renderer::getCube()
{
	return currentScene->getSceneObjects()[1];
}
