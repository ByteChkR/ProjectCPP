#include "Button.h"
#include "SFML\Graphics.hpp"
#include "RetryButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"
#include "../_vs2015/PlayerController.hpp"

RetryButton::RetryButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void RetryButton::OnClick()
{
	std::cout << "Retry" << std::endl;
	MapBuilder::instance->Reload();
	GameStateManager::instance->_state = GameStateManager::StateGame;
	PlayerController::instance->getOwner()->EnableBehaviours();
}