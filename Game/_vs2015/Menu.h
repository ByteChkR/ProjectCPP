#ifndef MENU_H
#define MENU_H

#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "Button.h"

class Menu
{
	public:
		Menu(sf::RenderWindow * aWindow);
		void draw();

	private:
		sf::RenderWindow * _window;

		HudText * _playText;
		HudSprite *_playBox;
		Button *_button;

		void _organizeMenu();

};

#endif
