#include "Button.h"
#include "SFML\Graphics.hpp"
#include "MenuButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"
#include "LevelManager.h"

MenuButton::MenuButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void MenuButton::OnClick()
{
	std::cout << "Menu" << std::endl;
	MapBuilder::instance->Reload();
	LevelManager::instance->ChangeLevel(0);
	GameStateManager::instance->_state = GameStateManager::StateMenu;
}