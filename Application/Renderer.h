#ifndef RENDERER_H
#define RENDERER_H

#include "../Game/Scene.h"
#include <map>

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

public:

	void loadScene();

private:

	bool isRunning = true; //TODO:: Delete this variable either here or scene
	bool isDirty;
	bool isLoadingScene = false;

	std::map<std::string, Scene> scenes;

	Scene* currentScene;
};
#endif

