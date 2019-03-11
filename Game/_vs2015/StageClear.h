#ifndef STAGECLEAR_H
#define STAGECLEAR_H

#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "Button.h"

class StageClear {
public:
	StageClear(sf::RenderWindow *aWindow);

	void Update();

private:
	void OrganizeScreen();
	void draw();

	sf::RenderWindow *_window;
	HudSprite *_background;
	HudSprite *_nextStageButtonBox;
	Button *_nextStageButton;
	HudSprite *_clearBox;
	HudSprite *_menuButtonBox;
	Button *_menuButton;

};

#endif
