#include "Button.h"
#include "SFML\Graphics.hpp"
#include "NextStageButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"
#include "LevelManager.h"
#include "MapBuilder.h"
#include "PlayerController.hpp"
#include "../_vs2015/Debug.h"
NextStageButton::NextStageButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite) {
	
}

void NextStageButton::OnClick() {
	Debug::Log("NextStage", ALL);
	LevelManager::instance->NextLevel();
	GameStateManager::instance->_state = GameStateManager::StatePanel;
}