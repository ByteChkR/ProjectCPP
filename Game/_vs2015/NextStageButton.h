#ifndef NEXTSTAGEBUTTON_H
#define NEXTSTAGEBUTTON_H

#include "Button.h"
#include "SFML\Graphics.hpp"

class NextStageButton : public Button
{
public:
	NextStageButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite);
private:

	void OnClick();
};

#endif
