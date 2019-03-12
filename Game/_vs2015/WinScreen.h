#ifndef WINSCREEN_H
#define WINSCREEN_H

#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "../_vs2015/KeyLogger.h"
#include "Button.h"

class WinScreen
{
public:
	WinScreen(sf::RenderWindow *aWindow);
	WinScreen();

	void SendScore();
	void ResetScoreSendBool();

	void Update();
private:
	void draw();
	void OrganizePanel();
	void TypeName();

	bool sendScore;
	bool _backSpace;
	std::string _nameString;

	KeyLogger *_kLogger;

	sf::RenderWindow *_window;
	HudSprite *_background;
	HudSprite* _nameBox;
	HudSprite *_sendScoreBox;
	Button *_sendScoreButton;
	HudText *_name;
};
#endif