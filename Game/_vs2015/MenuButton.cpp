#include "Button.h"
#include "SFML\Graphics.hpp"
#include "MenuButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"
#include "LevelManager.h"
#include "../_vs2015/Debug.h"
#include "../_vs2015/PlayerController.hpp"
MenuButton::MenuButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void MenuButton::OnClick()
{
	Debug::Log("Menu", ALL);
	PlayerController::instance->ResetScore();
	MapBuilder::instance->Reload();
	LevelManager::instance->ChangeLevel(0);
	GameStateManager::instance->_state = GameStateManager::StateMenu;
}