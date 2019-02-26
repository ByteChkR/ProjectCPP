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
		void Update();

	private:
		sf::RenderWindow * _window;

		HudSprite *_background;

		HudSprite *_playBox;
		Button *_button;


		HudSprite *_creditsBox;
		Button *_creditsButton;


		HudSprite *_scoreBoardBox;
		Button *_scoreBoardButton;

		HudSprite *_exitBox;
		Button *_exitButton;

		void _organizeMenu();

};

#endif
