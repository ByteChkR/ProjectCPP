#include <iostream>
#include "GameStateManager.h"
#include "mge\core\World.hpp"

GameStateManager::GameStateManager()
{
	GameStateManager::instance = this;
	_state = GameState(Game);
}

void GameStateManager::Update(float pTime ,World *_world) 
{
	switch (_state)
	{
	case GameStateManager::Menu:
		break;
	case GameStateManager::Game:
		_world->update(pTime);
		break;
	case GameStateManager::GameOver:
		break;
	default:
		break;
	}
}