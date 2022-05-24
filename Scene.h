#ifndef SCENE_H
#define SCENE_H

enum Primitive
{
	CUBE, QUAD
};
class Scene
{
public:
	Scene();
	~Scene();

public:
	void start();
	void update();
	void render();

public:

	void saveScene(); //TODO:: Save prefabs and information in the scene
	void loadPrefabs();

	void createEmpty();
	void createPrimitive(Primitive& primitive);
	void duplicateObject();
	void deleteObject(); //TODO::Add reference

private:

	bool isRunning; //TODO:: Delete this variable either here or gamestate
};
#endif
