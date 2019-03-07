#ifndef DEBUGHUD_HPP
#define DEBUGHUD_HPP

#include <SFML/Graphics.hpp>
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include"../_vs2015/Menu.h"
#include <iostream>

/**
 * Very simple class capable of rendering a simple piece of text through SFML.
 */
class DebugHud
{
	public:
		DebugHud( sf::RenderWindow * aWindow );
		virtual ~DebugHud();
		void draw();

		void setScore(int score);
		void setDebugInfo (std::string pInfo);

		void Update();
	private:
		sf::RenderWindow * _window;

		int _score = 0;

		HudText *_scoreText;
        HudText *_debugText;
		HudSprite *_debugBox;
		HudSprite* _scoreBackground;

		HudSprite *_progressBackground;
		HudSprite *_progress;

		//Menu *_menu;

		void _organizeHud();

        DebugHud(const DebugHud&);
        DebugHud& operator=(const DebugHud&);

};

#endif // DEBUGHUD_HPP
