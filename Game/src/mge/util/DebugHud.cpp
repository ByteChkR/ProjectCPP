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

DebugHud::DebugHud( sf::RenderWindow * aWindow ): _window( aWindow ), _debugText(), _debugBox()
{
	assert ( _window != NULL );

	_debugText = new HudText();
	_debugBox =  new HudSprite("HudBox.png");
	//_menu = new Menu(_window);

	_organizeHud();
}

DebugHud::~DebugHud()
{
	//dtor
}

void DebugHud::_organizeHud()
{
	_debugBox->sprite.setPosition(0, 0);
	_debugText->_text.setPosition(10, 10);

}

void DebugHud::setDebugInfo(std::string pInfo) {
    _debugText->_text.setString(pInfo);
	//_menu->Update();
}

void DebugHud::draw()
{
	//glDisable( GL_CULL_FACE );
	glActiveTexture(GL_TEXTURE0);
    _window->pushGLStates();
    _window->draw(_debugText->_text);
	_window->draw(_debugBox->sprite);
	_window->popGLStates();

	//_menu->draw();
}
