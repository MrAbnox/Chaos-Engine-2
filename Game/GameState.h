#ifndef GAMESTATE_H
#define GAMESTATE_H



class GameState
{
private:
	//TODO: Load file or create a new one
	GameState();
	GameState(const GameState&);
	GameState& operator = (GameState&);

public:

	static GameState* instance();
	
	void initialize();
	void run();
	
private:
	
	void update();
	void render();
	
public:
	
	void loadScene();

private:

	bool isRunning; //TODO:: Delete this variable either here or gamestate
	bool isDirty;
};

#endif