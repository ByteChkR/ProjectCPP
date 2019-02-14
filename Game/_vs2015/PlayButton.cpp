#include "Button.h"
#include "SFML\Graphics.hpp"
#include "PlayButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"

PlayButton::PlayButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void PlayButton::OnClick()
{
	std::cout << "Play" << std::endl;
	MapBuilder::instance->Reload();
	GameStateManager::instance->_state = GameStateManager::StateGame;
}