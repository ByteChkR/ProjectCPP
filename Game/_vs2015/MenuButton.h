#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "Button.h"
#include "SFML\Graphics.hpp"

class MenuButton : public Button
{
public:
	MenuButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite);

private:
	void OnClick();
};

#endif
