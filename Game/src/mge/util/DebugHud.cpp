#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include "mge/util/DebugHud.hpp"
#include "mge/config.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "mge/core/Texture.hpp"
#include "../_vs2015/PlayerController.hpp"
#include "../_vs2015/MapBuilder.h"



DebugHud::DebugHud( sf::RenderWindow * aWindow ): _window( aWindow ), _debugText(), _debugBox()
{
	assert ( _window != NULL );

	_debugText = new HudText();
	_scoreText = new HudText("Candy Beans.otf",26);
	_debugBox =  new HudSprite("HudBox.png");
	_scoreBackground = new HudSprite("score_background.png");

	_progressBackground = new HudSprite("run_meter2.png");
	_progress = new HudSprite("run_meter_turkey.png");
	//_progressBackground->sprite.setOrigin(_progressBackground->sprite.getTexture()->getSize().x / 2, _progressBackground->sprite.getTexture()->getSize().y);

	_organizeHud();
}

void DebugHud::setScore(int score) {
	_score = score;
	_scoreText->_text.setString("Score : " + std::to_string(_score));
}

DebugHud::~DebugHud()
{
	//dtor
}

void DebugHud::_organizeHud()
{
	_debugBox->sprite.setPosition(100, 100);
	_debugText->_text.setPosition(25, 75);

	_scoreText->_text.setPosition(100, 20);
	_scoreBackground->sprite.setPosition(_scoreText->_text.getPosition().x+ _scoreBackground->sprite.getTexture()->getSize().x / 4, _scoreText->_text.getPosition().y+20);

	_progressBackground->sprite.setPosition(60, 250);
	_progress->sprite.setPosition(_progressBackground->sprite.getPosition());

}

void DebugHud::Update() {
	draw();
	setScore(PlayerController::instance->GetCoinCount());
	float progressPosY = (_progressBackground->sprite.getPosition().y + _progressBackground->sprite.getTexture()->getSize().y / 2) - _progressBackground->sprite.getTexture()->getSize().y * MapBuilder::instance->GetProgress();
	_progress->sprite.setPosition(_progressBackground->sprite.getPosition().x, progressPosY);
}

void DebugHud::setDebugInfo(std::string pInfo) {
    _debugText->_text.setString(pInfo);
}

void DebugHud::draw()
{
	//glDisable( GL_CULL_FACE );
	glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates();

	_window->draw(_scoreBackground->sprite);
	_window->draw(_scoreText->_text);

   // _window->draw(_debugText->_text);
	//_window->draw(_debugBox->sprite);

	_window->draw(_progressBackground->sprite);
	_window->draw(_progress->sprite);

	_window->popGLStates();
}
