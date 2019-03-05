#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "Button.h"
#include "mge\util\ScoreManager.h"

class ScoreBoard {
public:
	ScoreBoard(sf::RenderWindow *aWindow);

	void Update();
	void ResetScoreUpdate();
private:
	void UpdateScores();
	void OrganizeScreen();
	void draw();

	bool _updatedScores;

	int _size;
	
	std::vector<ScoreManager::Score> _scores;

	std::vector<HudText*> _nameDisplays;
	std::vector<HudText*> _scoreDisplays;

	HudSprite *_menuButtonBox;
	Button *_menuButton;

	sf::RenderWindow *_window;
	HudSprite *_background;
	HudSprite *_scoreBoard;
};

#endif
