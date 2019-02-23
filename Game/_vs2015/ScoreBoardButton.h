#ifndef SCOREBOARDBUTTON_H
#define SCOREBOARDBUTTON_H

#include "Button.h"
#include "SFML\Graphics.hpp"

class ScoreBoardButton : public Button
{
public:
	ScoreBoardButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite);

private:
	void OnClick();
};

#endif