#ifndef TUTORIAL3_HPP
#define TUTORIAL3_HPP

#include <SFML/Graphics.hpp>
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include"../_vs2015/Menu.h"
#include <iostream>

/**
* Very simple class capable of rendering a simple piece of text through SFML.
*/
class Tutorial3
{
public:
	Tutorial3(sf::RenderWindow * aWindow);
	void draw();

	void Update();
private:
	sf::RenderWindow * _window;

	HudSprite *_debugBox;

	void ButtonPressCheck();
	void _organizeHud();
};

#endif // TUTORIAL1_HPP
