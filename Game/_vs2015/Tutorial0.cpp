#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include "Tutorial0.h"
#include "mge/config.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "mge/core/Texture.hpp"
#include "../_vs2015/PlayerController.hpp"
#include "../_vs2015/MapBuilder.h"
#include "GameStateManager.h"
#include "../_vs2015/Debug.h"

Tutorial0::Tutorial0(sf::RenderWindow * aWindow) : _window(aWindow), _debugBox()
{

	_debugBox = new HudSprite("Tutorials/Tutorial0.png");

	_organizeHud();
}

void Tutorial0::ButtonPressCheck()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		GameStateManager::instance->_state = GameStateManager::StateGame;
		Debug::Log("Next Tutorial");
	}
}

void Tutorial0::_organizeHud()
{
	_debugBox->sprite.setPosition(300, 300);
}

void Tutorial0::Update() {
	draw();
	ButtonPressCheck();
}

void Tutorial0::draw()
{
	//glDisable( GL_CULL_FACE );
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_debugBox->sprite);

	_window->popGLStates();
}