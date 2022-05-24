#ifndef GAMESTATE_H
#define GAMESTATE_H



class GameState
{
public:
	//TODO: Load file or create a new one
	GameState();
	~GameState();

public:

	void loadScene();
	void update();
	void render();

private:

	bool isRunning; //TODO:: Delete this variable either here or gamestate
	bool isDirty;
};

#endif