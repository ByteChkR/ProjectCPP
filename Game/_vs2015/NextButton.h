#ifndef NEXTBUTTON_H
#define NEXTBUTTON_H

#include "Button.h"
#include "SFML\Graphics.hpp"
#include "../_vs2015/StoryPanel.h"
#include "StoryPanel.h"

class NextButton : public Button
{
public:
	NextButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite, StoryPanel *panel);
	StoryPanel* _panel;
	virtual void Update() override;
private:

	void OnClick();
};

#endif