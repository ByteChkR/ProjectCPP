#ifndef RETRYBUTTON_H
#define RETRYBUTTON_H

#include "Button.h"
#include "SFML\Graphics.hpp"

class RetryButton : public Button
{
public:
	RetryButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite);

private:
	void OnClick();
};

#endif