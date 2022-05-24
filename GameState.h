#ifndef GAMESTATE_H
#define GAMESTATE_H

enum Primitive
{
	CUBE, QUAD
};

class GameState
{
public:
	//TODO: Load file or create a new one
	GameState();
	~GameState();

public:

	void start();
	void update();
	void render();

public:

	void createEmpty();
	void createPrimitive(Primitive& primitive);
	void duplicateObject();
	void deleteObject(); //TODO::Add reference

private:

	void loadPrefabs();

	bool isRunning;
};

#endif