#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include "Tutorial3.h"
#include "mge/config.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "mge/core/Texture.hpp"
#include "../_vs2015/PlayerController.hpp"
#include "../_vs2015/MapBuilder.h"
#include "GameStateManager.h"
#include "../_vs2015/Debug.h"

Tutorial3::Tutorial3(sf::RenderWindow * aWindow) : _window(aWindow), _debugBox()
{

	_debugBox = new HudSprite("HudBox.png");

	_organizeHud();
}

void Tutorial3::ButtonPressCheck()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		GameStateManager::instance->_state = GameStateManager::StateGame;
		Debug::Log("Next Tutorial");
	}
}

void Tutorial3::_organizeHud()
{
	_debugBox->sprite.setPosition(300, 300);
}

void Tutorial3::Update() {
	draw();
	ButtonPressCheck();
}

void Tutorial3::draw()
{
	//glDisable( GL_CULL_FACE );
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_debugBox->sprite);

	_window->popGLStates();
}