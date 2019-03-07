#include "Button.h"
#include "SFML\Graphics.hpp"
#include "ExitButton.h"
#include <iostream>
#include "../_vs2015/Debug.h"
ExitButton::ExitButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{
	_window = aWindow;
}

void ExitButton::OnClick()
{
	Debug::Log("Exit", ALL);
	_window->close();
}