#include "Button.h"
#include "SFML\Graphics.hpp"
#include "ScoreBoardButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"
#include "../_vs2015/Debug.h"
ScoreBoardButton::ScoreBoardButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void ScoreBoardButton::OnClick()
{
	Debug::Log("ScoreBoard");
	GameStateManager::instance->_state = GameStateManager::StateScore;
}