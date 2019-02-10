#include <iostream>
#include "GameStateManager.h"

GameStateManager::GameStateManager()
{
	_state = GameState(Menu);
}

void GameStateManager::Update() 
{
	switch (_state)
	{
	case GameStateManager::Menu:
		break;
	case GameStateManager::Game:
		break;
	case GameStateManager::GameOver:
		break;
	default:
		break;
	}
}