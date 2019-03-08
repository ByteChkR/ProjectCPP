#ifndef PANELBACKBUTTON_H
#define PANELBACKBUTTON_H

#include "Button.h"
#include "SFML\Graphics.hpp"
#include "../_vs2015/StoryPanel.h"
#include "StoryPanel.h"

class PanelBackButton : public Button
{
public:
	PanelBackButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite, StoryPanel *panel);
	StoryPanel* _panel;
private:

	void OnClick();
};

#endif
