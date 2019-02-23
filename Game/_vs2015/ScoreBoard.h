#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "Button.h"

class ScoreBoard {
public:
	ScoreBoard(sf::RenderWindow *aWindow);

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
