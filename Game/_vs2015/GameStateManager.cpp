#include <iostream>
#include "GameStateManager.h"
#include "mge\core\World.hpp"

GameStateManager *GameStateManager::instance;

GameStateManager::GameStateManager(GameStateManager::GameState state)
{
	GameStateManager::instance = this;
	_state = GameState(state);
}

void GameStateManager::Update(float pTime ,World *_world) 
{
	switch (_state)
	{
	case GameStateManager::StateMenu:
		
		break;
	case GameStateManager::StatePanel:
		break;
	case GameStateManager::StateGame:
		if (_world != nullptr) _world->update(pTime); 
		break;
	case GameStateManager::StateGameOver:
		break;
	case GameStateManager::Tutorial1:
		if (_world != nullptr) _world->update(pTime);
		break;
	case GameStateManager::Tutorial2:
		if (_world != nullptr) _world->update(pTime);
		break;
	case GameStateManager::Tutorial3:
		if (_world != nullptr) _world->update(pTime);
		break;
	case GameStateManager::Tutorial4:
		if (_world != nullptr) _world->update(pTime);
		break;
	default:
		break;
	}
}