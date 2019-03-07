#include "Button.h"
#include "SFML\Graphics.hpp"
#include "NextButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"
#include "../_vs2015/Debug.h"
NextButton::NextButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite,StoryPanel* panel) : Button(aWindow, _buttonSprite){
	_panel = panel;
}

void NextButton::OnClick(){
	Debug::Log("Next", ALL);
	_panel->NextPanel();
}