#ifndef PLAYBUTTON_H
#define PLAYBUTTON_H

#include "Button.h"
#include "SFML\Graphics.hpp"

class PlayButton : public Button
{
	public:
		PlayButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite);

	private:
		void OnClick();
};

#endif
