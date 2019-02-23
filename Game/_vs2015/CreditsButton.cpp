#include "Button.h"
#include "SFML\Graphics.hpp"
#include "CreditsButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"

CreditsButton::CreditsButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void CreditsButton::OnClick()
{
	std::cout << "Credits" << std::endl;
	GameStateManager::instance->_state = GameStateManager::StateCredits;
}