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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	std::shared_ptr<Material> mat2 = std::make_shared<Material>(DEFAULT);
	mat2->setShader(loadedShaders["Default"]);
	loadedMaterials["Default"] = mat2;
	loadedMaterials["Default"]->setShader(loadedShaders["Default"]);
}

void Renderer::loadGameObjects()
{
	//TODO: Automate this system with a prefab system (File reading)
	
	// Cube
	//________________________________________________________________________________
	std::shared_ptr<GameObject> obj1 = std::make_shared<GameObject>();
	std::shared_ptr<MeshRenderer> temp = obj1->addComponent<MeshRenderer>();
	std::shared_ptr<Mesh> mesh = std::make_shared<Primitive>();
	mesh->setup();
	temp->setMaterial(loadedMaterials["Skybox"]);
	temp->setMesh(mesh);
	loadedGameObjects["Cube"] = obj1;

	// Floor
	//________________________________________________________________________________
	std::shared_ptr<GameObject> obj2 = std::make_shared<GameObject>();
	std::shared_ptr<Mesh> model = std::make_shared<Model>("Default", "car/GR_Ceiling.obj", "car/bricks2.jpg");
	std::shared_ptr<GameObject> floor = std::make_shared<GameObject>();
	std::shared_ptr<MeshRenderer> temp2 = obj2->addComponent<MeshRenderer>();
	temp2->setMaterial(loadedMaterials["Default"]);
	temp2->setMesh(model);
	model->setupMaterial(loadedMaterials["Default"]);
	loadedGameObjects["Floor"] = obj2;

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

std::shared_ptr<Material> Renderer::getMat(std::string name)
{
	return loadedMaterials[name];
}
