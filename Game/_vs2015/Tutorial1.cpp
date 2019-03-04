#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include "Tutorial1.h"
#include "mge/config.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "mge/core/Texture.hpp"
#include "../_vs2015/PlayerController.hpp"
#include "../_vs2015/MapBuilder.h"
#include "GameStateManager.h"
#include "../_vs2015/Debug.h"

Tutorial1::Tutorial1(sf::RenderWindow * aWindow) : _window(aWindow), _debugBox()
{

	_debugBox = new HudSprite("HudBox.png");

	_organizeHud();
}

void Tutorial1::ButtonPressCheck()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		GameStateManager::instance->_state = GameStateManager::Tutorial3;
		Debug::Log("Next Tutorial");
	}
}

void Tutorial1::_organizeHud()
{
	_debugBox->sprite.setPosition(300, 300);
}

void Tutorial1::Update() {
	draw();
	ButtonPressCheck();
}

void Tutorial1::draw()
{
	//glDisable( GL_CULL_FACE );
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_debugBox->sprite);

	_window->popGLStates();
}