#include "Button.h"
#include "SFML\Graphics.hpp"
#include "PlayButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"
#include "../_vs2015/PlayerController.hpp"

PlayButton::PlayButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void PlayButton::OnClick()
{
	std::cout << "Play" << std::endl;
	MapBuilder::instance->Reload();
	GameStateManager::instance->_state = GameStateManager::StatePanel;
	PlayerController::instance->getOwner()->EnableBehaviours();
}