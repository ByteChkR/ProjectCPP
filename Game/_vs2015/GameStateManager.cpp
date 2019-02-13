#include <iostream>
#include "GameStateManager.h"
#include "mge\core\World.hpp"

GameStateManager *GameStateManager::instance;

GameStateManager::GameStateManager()
{
	GameStateManager::instance = this;
	_state = GameState(StateMenu);
}

void GameStateManager::Update(float pTime ,World *_world) 
{
	switch (_state)
	{
	case GameStateManager::StateMenu:
		
		break;
	case GameStateManager::StateGame:
		if (_world != nullptr) _world->update(pTime); 
		break;
	case GameStateManager::StateGameOver:
		break;
	default:
		break;
	}
}