#include "Menu.h"
#include <cassert>
#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "Button.h"
#include <iostream>
#include <GL/glew.h>

Menu::Menu(sf::RenderWindow *aWindow) : _window(aWindow)
{
	assert(_window != NULL);

	_playText = new HudText();
	_playBox = new HudSprite("HudBox.png");

	_button = new Button(_window,_playBox->sprite);
}

void Menu::_organizeMenu() 
{
	_playText->_text.setString("PLAY");
	_playText->_text.setPosition(100, 100);
	_playBox->sprite.setPosition(100, 100);
}

void Menu::draw() 
{
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();
	_window->draw(_playText->_text);
	_window->draw(_playBox->sprite);

	_window->popGLStates();
}