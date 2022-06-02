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
	//glEnable(GL_FRAMEBUFFER_SRGB);
	//if(!isLoadingScene)
	currentScene->render();

	//glDisable(GL_FRAMEBUFFER_SRGB);
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

	std::shared_ptr<Shader> temp3 = std::make_shared<Shader>("shaders/water.vert", "shaders/water.frag");
	loadedShaders["Water"] = temp3;
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

	std::shared_ptr<Material> mat3 = std::make_shared<Material>(DEFAULT);
	mat3->setShader(loadedShaders["Water"]);
	loadedMaterials["Water"] = mat3;
	loadedMaterials["Water"]->setShader(loadedShaders["Water"]);

}

void Renderer::loadGameObjects()
{
	//TODO: Automate this system with a prefab system (File reading)
	
	// Cube
	//________________________________________________________________________________
	std::shared_ptr<GameObject> obj1 = std::make_shared<GameObject>();
	std::shared_ptr<MeshRenderer> temp = obj1->addComponent<MeshRenderer>();
	temp->setShader("Skybox");
	std::shared_ptr<Mesh> mesh = std::make_shared<Primitive>();
	mesh->setup();
	temp->setMaterial(loadedMaterials["Skybox"]);
	temp->setMesh(mesh);
	loadedGameObjects["Cube"] = obj1;

	// Nintendo Wii
	//________________________________________________________________________________
	std::shared_ptr<GameObject> obj2 = std::make_shared<GameObject>();
	std::shared_ptr<Mesh> model = std::make_shared<Model>("Default", "car/GR_NintendoWii.obj");
	std::shared_ptr<MeshRenderer> temp2 = obj2->addComponent<MeshRenderer>();
	temp2->setMesh(model);
	temp2->setShader("Default");
	temp2->setMaterial(loadedMaterials["Default"]);
	model->setupMaterial(loadedMaterials["Default"]);
	model->getMaterial()->loadTexture("car/GR_NintendoWii_Diffuse.png");
	obj2->setName("Wii");
	loadedGameObjects["Nintendo"] = obj2;

	//Cube (Water)
	//________________________________________________________________________________
	std::shared_ptr<GameObject> obj3 = std::make_shared<GameObject>();
	obj3->getTransform()->setPos(glm::vec3(1.0f, -3.0f, -15.0f));
	obj3->getTransform()->setScale(glm::vec3(20.0f, 1.0f, 20.0f));
	std::shared_ptr<Mesh> model2 = std::make_shared<Model>("Water", "car/cube.obj");
	std::shared_ptr<MeshRenderer> temp3 = obj3->addComponent<MeshRenderer>();
	temp3->setShader("Water");
	temp3->setMaterial(loadedMaterials["Water"]);
	temp3->setMesh(model2);
	model2->setupMaterial(loadedMaterials["Water"]);
	obj3->setName("Water");
	loadedGameObjects["Water"] = obj3;

	// Camera
	//________________________________________________________________________________
	std::shared_ptr<GameObject> cam = std::make_shared<GameObject>();
	cam->addComponent<Camera>();
	cam->setName("Camera");
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
