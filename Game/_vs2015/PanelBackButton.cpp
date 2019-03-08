#include "Button.h"
#include "SFML\Graphics.hpp"
#include "PanelBackButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"
#include "../_vs2015/Debug.h"
PanelBackButton::PanelBackButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite, StoryPanel* panel) : Button(aWindow, _buttonSprite) {
	_panel = panel;
}

void PanelBackButton::OnClick() {
	Debug::Log("Back", ALL);
	_panel->PreviousPanel();
}