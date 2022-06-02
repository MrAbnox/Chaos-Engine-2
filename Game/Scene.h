#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"

enum Prim
{
	CUBE, QUAD
};

class Scene
{
public:
	Scene();

public:
	void load();
	void start();
	void update();
	void render();
	

	void setupDepthBuffer();
	void sendDepthBuffer();
	void restorePass();

public:

	void saveScene(); //TODO:: Save prefabs and information in the scene
	void unload(); //unload objects if need to be!


	std::shared_ptr<GameObject> createEmpty(); //Create Empty Object
	void createPrimitive(Prim primitive, glm::vec3& pos = glm::vec3(0.0f)); //Create Primitive Object
	void duplicateObject(); //Duplicate Object in the same position
	void deleteObject(); //TODO::Add reference
	void addObjectToScene(const std::shared_ptr<GameObject> object); //Add Object to the scene

public:

	std::vector<std::shared_ptr<GameObject>> getSceneObjects();

private:

	bool isRunning; //TODO:: Delete this variable either here or renderer
	GLuint gDepth;

	GLuint gBuffer;
	GLuint accumBuffer;
	std::vector<std::shared_ptr<GameObject>> sceneObjects;
};
#endif
