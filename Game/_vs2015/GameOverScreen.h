#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "Button.h"

class GameOverScreen{
	public:
		GameOverScreen(sf::RenderWindow *aWindow);

		void Update();
		void SetProgressAchieved(float pProgress);
	private:
		void OrganizeScreen();
		void draw();

		int _progress;

		sf::RenderWindow *_window;
		HudSprite *_background;
		HudSprite *_retryButtonBox;
		Button *_retryButton;

		HudText *_progressText;
		HudSprite *_GameOverBox;
		HudSprite *_menuButtonBox;
		Button *_menuButton;

};

#endif
