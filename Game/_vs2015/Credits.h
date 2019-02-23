#ifndef CREDITS_H
#define CREDITS_H

#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "Button.h"

class Credits {
public:
	Credits(sf::RenderWindow *aWindow);

	void Update();

private:
	void OrganizeScreen();
	void draw();

	HudText *_menuText;
	HudSprite *_menuButtonBox;
	Button *_menuButton;

	sf::RenderWindow *_window;
	HudSprite *_background;
};

#endif

