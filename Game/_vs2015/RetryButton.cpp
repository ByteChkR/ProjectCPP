#include "Button.h"
#include "SFML\Graphics.hpp"
#include "RetryButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"

RetryButton::RetryButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void RetryButton::OnClick()
{
	std::cout << "Retry" << std::endl;
	MapBuilder::instance->Reload();
	GameStateManager::instance->_state = GameStateManager::StateGame;
}