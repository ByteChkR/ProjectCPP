#include "Button.h"
#include "SFML\Graphics.hpp"
#include "PlayButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"
#include "../_vs2015/PlayerController.hpp"
#include "../_vs2015/Debug.h"
#include "mge/MGEDemo.hpp"
PlayButton::PlayButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void PlayButton::OnClick()
{
	Debug::Log("Play", ALL);
	MapBuilder::instance->Reload();
	if (MGEDemo::instance->CurrentGameMode == MGEDemo::GameMode::STORY)
		GameStateManager::instance->_state = GameStateManager::StatePanel;
	else
		GameStateManager::instance->_state = GameStateManager::StateGame;
	PlayerController::instance->getOwner()->EnableBehaviours();
	PlayerController::instance->Reset();
}