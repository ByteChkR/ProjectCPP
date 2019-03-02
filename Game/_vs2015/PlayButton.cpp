#include "Button.h"
#include "SFML\Graphics.hpp"
#include "PlayButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"
#include "../_vs2015/PlayerController.hpp"
#include "../_vs2015/Debug.h"
PlayButton::PlayButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void PlayButton::OnClick()
{
	Debug::Log("Play");
	MapBuilder::instance->Reload();
	GameStateManager::instance->_state = GameStateManager::StatePanel;
	PlayerController::instance->getOwner()->EnableBehaviours();
}