#include "GameState.h"

GameState::GameState()
{
}

GameState::~GameState()
{
}

GameState* GameState::instance()
{
	static GameState* gameState = new GameState;
	return gameState;
}

void GameState::initialize()
{
}

void GameState::run()
{
	update();
	render();
}

void GameState::update()
{
}

void GameState::render()
{
}

void GameState::loadScene()
{
}
