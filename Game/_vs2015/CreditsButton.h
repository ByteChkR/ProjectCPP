#ifndef CREDITSBUTTON_H
#define CREDITSBUTTON_H

#include "Button.h"
#include "SFML\Graphics.hpp"

class CreditsButton : public Button
{
public:
	CreditsButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite);

private:
	void OnClick();
};

#endif