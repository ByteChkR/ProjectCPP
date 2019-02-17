#ifndef WINSCREEN_H
#define WINSCREEN_H

#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "Button.h"

class WinScreen
{
public:
	WinScreen(sf::RenderWindow *aWindow);
	WinScreen();

	void Update();
private:
	void draw();
	void OrganizePanel();

	sf::RenderWindow *_window;
	HudSprite *_background;
	HudSprite *_menuButtonBox;
	Button *_menuButton;
	HudText *_menuText;
	HudText *_winText;
};
#endif