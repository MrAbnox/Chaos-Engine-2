#ifndef RENDERER_H
#define RENDERER_H

#include "../Game/Scene.h"
#include <map>
#include "../Game/Primitive.h"

class Renderer
{
private:
	//TODO: Load file or create a new one
	Renderer() {};
	Renderer(const Renderer&);
	Renderer& operator = (Renderer&);

public:
	static Renderer* instance();
	void initialize();
	void run();
	

private:
	void update();
	void render();
	
	void loadScene();
	void loadShaders();
	void loadMaterials();
	void loadGameObjects();

public:
	std::shared_ptr<GameObject> getObject(std::string name);
	Shader getShader(std::string name);
	std::shared_ptr<GameObject> getCube();
	
private:

	bool isRunning = true; //TODO:: Delete this variable either here or scene
	bool isDirty;
	bool isLoadingScene = false;

	Scene* currentScene;
	
	std::map<std::string, Scene> scenes;
	std::map<std::string, std::shared_ptr<GameObject>> loadedGameObjects;
	std::map<std::string, std::shared_ptr<Material>> loadedMaterials;
	std::map<std::string, std::shared_ptr<Shader>> loadedShaders;

};
#endif

