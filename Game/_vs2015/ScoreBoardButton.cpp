#include "Button.h"
#include "SFML\Graphics.hpp"
#include "ScoreBoardButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"

ScoreBoardButton::ScoreBoardButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void ScoreBoardButton::OnClick()
{
	std::cout << "ScoreBoard" << std::endl;
	MapBuilder::instance->Reload();
	GameStateManager::instance->_state = GameStateManager::StateScore;
}