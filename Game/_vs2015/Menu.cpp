#include "Menu.h"
#include <cassert>
#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "Button.h"
#include "PlayButton.h"
#include "ExitButton.h"
#include "ScoreBoardButton.h"
#include "CreditsButton.h"
#include <iostream>
#include <GL/glew.h>

Menu::Menu(sf::RenderWindow *aWindow) : _window(aWindow)
{
	assert(_window != NULL);

	_background = new HudSprite("tempMenu.png");

	_playText = new HudText();
	_playBox = new HudSprite("HudBox.png",0.8f);
	_button = new PlayButton(_window,_playBox->sprite);

	_creditsText = new HudText();
	_creditsBox = new HudSprite("HudBox.png", 0.8f);
	_creditsButton = new CreditsButton(_window, _creditsBox->sprite);

	_scoreBoardText = new HudText();
	_scoreBoardBox = new HudSprite("HudBox.png", 0.8f);
	_scoreBoardButton = new ScoreBoardButton(_window, _scoreBoardBox->sprite);

	_exitText = new HudText();
	_exitBox = new HudSprite("HudBox.png",0.8f);
	_exitButton = new ExitButton(_window, _exitBox->sprite);

	_organizeMenu();
}

void Menu::_organizeMenu() 
{
	_background->sprite.setPosition(_background->sprite.getTexture()->getSize().x / 2, _background->sprite.getTexture()->getSize().y / 2);

	_playText->_text.setString("PLAY");
	_playBox->sprite.setPosition(100, 100);
	_playText->_text.setPosition(_playBox->sprite.getPosition());
	_playBox->scaledSprite.setPosition(_playBox->sprite.getPosition());
	_button->SetPosition(_playBox->sprite.getPosition());

	_scoreBoardText->_text.setString("ScoreBoard");
	_scoreBoardBox->sprite.setPosition(100, 200);
	_scoreBoardText->_text.setPosition(_scoreBoardBox->sprite.getPosition());
	_scoreBoardBox->scaledSprite.setPosition(_scoreBoardBox->sprite.getPosition());
	_scoreBoardButton->SetPosition(_scoreBoardBox->sprite.getPosition());

	_creditsText->_text.setString("Credits");
	_creditsBox->sprite.setPosition(100, 300);
	_creditsText->_text.setPosition(_creditsBox->sprite.getPosition());
	_creditsBox->scaledSprite.setPosition(_creditsBox->sprite.getPosition());
	_creditsButton->SetPosition(_creditsBox->sprite.getPosition());

	_exitText->_text.setString("Exit");
	_exitBox->sprite.setPosition(100, 400);
	_exitText->_text.setPosition(_exitBox->sprite.getPosition());
	_exitBox->scaledSprite.setPosition(_exitBox->sprite.getPosition());
	_exitButton->SetPosition(_exitBox->sprite.getPosition());
}

void Menu::Update() 
{
	_button->Update();
	_exitButton->Update();
	_creditsButton->Update();
	_scoreBoardButton->Update();
	draw();
}

void Menu::draw() 
{
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_background->sprite);

	if (_button->scaled)_window->draw(_playBox->scaledSprite);
	else _window->draw(_playBox->sprite);
	_window->draw(_playText->_text);

	if (_creditsButton->scaled)_window->draw(_creditsBox->scaledSprite);
	else _window->draw(_creditsBox->sprite);
	_window->draw(_creditsText->_text);

	if (_scoreBoardButton->scaled)_window->draw(_scoreBoardBox->scaledSprite);
	else _window->draw(_scoreBoardBox->sprite);
	_window->draw(_scoreBoardText->_text);

	if(_exitButton->scaled)_window->draw(_exitBox->scaledSprite);
	else _window->draw(_exitBox->sprite);
	_window->draw(_exitText->_text);

	_window->popGLStates();
}