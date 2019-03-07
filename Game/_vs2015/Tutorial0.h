#ifndef TUTORIAL0_HPP
#define TUTORIAL0_HPP

#include <SFML/Graphics.hpp>
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include"../_vs2015/Menu.h"
#include <iostream>

/**
* Very simple class capable of rendering a simple piece of text through SFML.
*/
class Tutorial0
{
public:
	Tutorial0(sf::RenderWindow * aWindow);
	void draw();

	void Update();
private:
	sf::RenderWindow * _window;

	HudSprite *_debugBox;

	void ButtonPressCheck();
	void _organizeHud();
};

#endif // TUTORIAL1_HPP
