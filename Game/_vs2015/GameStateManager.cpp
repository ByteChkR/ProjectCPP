#include <iostream>
#include "GameStateManager.h"
#include "mge\core\World.hpp"

GameStateManager *GameStateManager::instance;

GameStateManager::GameStateManager()
{
	GameStateManager::instance = this;
	_state = GameState(Menu);
}

void GameStateManager::Update(float pTime ,World *_world) 
{
	switch (_state)
	{
	case GameStateManager::Menu:
		break;
	case GameStateManager::Game:
		if (_world != nullptr) _world->update(pTime); 
		break;
	case GameStateManager::GameOver:
		break;
	default:
		break;
	}
}