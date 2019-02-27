#ifndef EXITBUTTON_H
#define EXITBUTTON_H

#include "Button.h"
#include "SFML\Graphics.hpp"

class ExitButton : public Button
{
public:
	ExitButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite);

private:
	sf::RenderWindow* _window;
	void OnClick();
};

#endif
