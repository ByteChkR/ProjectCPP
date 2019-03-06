#include "Button.h"
#include "SFML\Graphics.hpp"
#include "SaveScoreButton.h"
#include <iostream>
#include "../_vs2015/GameStateManager.h"
#include "../_vs2015/Debug.h"
SaveScoreButton::SaveScoreButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite, WinScreen *_winScreen) : Button(aWindow, _buttonSprite) {
	winScreen = _winScreen;
}

void SaveScoreButton::OnClick() {
	Debug::Log("SaveScore", ALL);
	winScreen->SendScore();
}