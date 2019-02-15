#include "Menu.h"
#include <cassert>
#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "Button.h"
#include "PlayButton.h"
#include "ExitButton.h"
#include <iostream>
#include <GL/glew.h>

Menu::Menu(sf::RenderWindow *aWindow) : _window(aWindow)
{
	assert(_window != NULL);

	_background = new HudSprite("tempMenu.png");

	_playText = new HudText();
	_playBox = new HudSprite("HudBox.png");
	_button = new PlayButton(_window,_playBox->sprite);

	_exitText = new HudText();
	_exitBox = new HudSprite("HudBox.png");
	_exitButton = new ExitButton(_window, _exitBox->sprite);

	_organizeMenu();
}

void Menu::_organizeMenu() 
{
	_playText->_text.setString("PLAY");
	_playText->_text.setPosition(70, 120);
	_playBox->sprite.setPosition(50, 100);
	_button->SetPosition(50, 100);

	_exitText->_text.setString("Exit");
	_exitText->_text.setPosition(70, 320);
	_exitBox->sprite.setPosition(50, 300);
	_exitButton->SetPosition(50, 300);
}

void Menu::Update() 
{
	_button->Update();
	_exitButton->Update();
	draw();
}

void Menu::draw() 
{
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_background->sprite);

	_window->draw(_playText->_text);
	_window->draw(_playBox->sprite);

	_window->draw(_exitText->_text);
	_window->draw(_exitBox->sprite);

	_window->popGLStates();
}