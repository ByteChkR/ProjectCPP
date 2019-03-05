#ifndef SAVESCOREBUTTON_H
#define SAVESCOREBUTTON_H

#include "Button.h"
#include "SFML\Graphics.hpp"
#include "../_vs2015/StoryPanel.h"
#include "StoryPanel.h"
#include "WinScreen.h"

class SaveScoreButton : public Button
{
public:
	SaveScoreButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite, WinScreen* _winScreen);
	WinScreen* winScreen;
private:

	void OnClick();
};

#endif