#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"

enum Primitive
{
	CUBE, QUAD
};

class Scene
{
public:
	Scene();

public:
	void start();
	void update();
	void render();

public:

	void saveScene(); //TODO:: Save prefabs and information in the scene
	void unload(); //unload objects if need to be!


	void createEmpty(); //Create Empty Object
	void createPrimitive(Primitive& primitive); //Create Primitive Object
	void duplicateObject(); //Duplicate Object in the same position
	void deleteObject(); //TODO::Add reference

public:

	std::vector<std::shared_ptr<GameObject>> getSceneObjects();

private:

	bool isRunning; //TODO:: Delete this variable either here or gamestate

	std::vector<std::shared_ptr<GameObject>> sceneObjects;
};
#endif
