#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "Button.h"

class LoadingScreen {
public:
	LoadingScreen(sf::RenderWindow *aWindow);

	void Update();

private:
	void OrganizeScreen();
	void draw();

	sf::RenderWindow *_window;
	HudSprite *_background;
};

#endif
