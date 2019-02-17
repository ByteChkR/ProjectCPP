#include "Button.h"
#include "SFML\Graphics.hpp"
#include "NextStageButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"
#include "LevelManager.h"

NextStageButton::NextStageButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite) {
	
}

void NextStageButton::OnClick() {
	std::cout << "NextStage" << std::endl;
	GameStateManager::instance->_state = GameStateManager::StateLoad;
	LevelManager::instance->NextLevel();
	GameStateManager::instance->_state = GameStateManager::StatePanel;
}