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

	_background = new HudSprite("turkey_mainmenu.png");

	_playBox = new HudSprite("play_button.png", 1.05f);
	_button = new PlayButton(_window, _playBox->sprite);

	_creditsBox = new HudSprite("credits_button.png", 1.05f);
	_creditsButton = new CreditsButton(_window, _creditsBox->sprite);

	_scoreBoardBox = new HudSprite("scoreboard_button.png", 1.05f);
	_scoreBoardButton = new ScoreBoardButton(_window, _scoreBoardBox->sprite);

	_exitBox = new HudSprite("exit_button.png", 1.05f);
	_exitButton = new ExitButton(_window, _exitBox->sprite);

	_organizeMenu();
}

void Menu::_organizeMenu()
{
	float xoffset = _window->getSize().x < 1920 ? 420 : 1500; //Sheeeeesh 420

	_background->sprite.setPosition(_background->sprite.getTexture()->getSize().x / 2, _background->sprite.getTexture()->getSize().y / 2);

	_playBox->sprite.setPosition(xoffset, 200);
	_playBox->scaledSprite.setPosition(_playBox->sprite.getPosition());
	_button->SetPosition(_playBox->sprite.getPosition());

	_scoreBoardBox->sprite.setPosition(xoffset, 350);
	_scoreBoardBox->scaledSprite.setPosition(_scoreBoardBox->sprite.getPosition());
	_scoreBoardButton->SetPosition(_scoreBoardBox->sprite.getPosition());

	_creditsBox->sprite.setPosition(xoffset, 475);
	_creditsBox->scaledSprite.setPosition(_creditsBox->sprite.getPosition());
	_creditsButton->SetPosition(_creditsBox->sprite.getPosition());

	_exitBox->sprite.setPosition(xoffset, 600);
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

	if (_creditsButton->scaled)_window->draw(_creditsBox->scaledSprite);
	else _window->draw(_creditsBox->sprite);

	if (_scoreBoardButton->scaled)_window->draw(_scoreBoardBox->scaledSprite);
	else _window->draw(_scoreBoardBox->sprite);

	if (_exitButton->scaled)_window->draw(_exitBox->scaledSprite);
	else _window->draw(_exitBox->sprite);

	_window->popGLStates();
}