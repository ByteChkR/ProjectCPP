#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include "mge/util/DebugHud.hpp"
#include "mge/config.hpp"
#include "../_vs2015/HudSprite.h"
#include "mge/core/Texture.hpp"

DebugHud::DebugHud( sf::RenderWindow * aWindow ): _window( aWindow ), _debugInfo(), _font(), _debugText(), _debugBox()
{
	assert ( _window != NULL );

    if (!_font.loadFromFile(config::MGE_FONT_PATH+ "arial.ttf")) {
        std::cout << "Could not load font, exiting..." << std::endl;
        return;
    }

	/*
	if (!_texture.loadFromFile(config::MGE_TEXTURE_PATH+ "HudBox.png")) {
		std::cout << "Could not load texture, exiting..." << std::endl;
		return;
	}

	_hudBox.setTexture(_texture);
	*/

	_debugBox =  new HudSprite("HudBox.png");

	_organizeHud();
    _createDebugHud();
}

DebugHud::~DebugHud()
{
	//dtor
}

void DebugHud::_organizeHud()
{
	_debugBox->sprite.setPosition(0, 0);

}

void DebugHud::_createDebugHud() {
    _debugText.setString("");
    _debugText.setFont(_font);
	_debugText.setCharacterSize(16);
	_debugText.setFillColor(sf::Color::White);
}

void DebugHud::setDebugInfo(std::string pInfo) {
    _debugText.setString(pInfo);
	_debugText.setPosition(10, 10);
}

void DebugHud::draw()
{
	//glDisable( GL_CULL_FACE );
	glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates();
    _window->draw(_debugText);
	_window->draw(_debugBox->sprite);
	_window->popGLStates();
}
