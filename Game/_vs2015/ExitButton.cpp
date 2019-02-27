#include "Button.h"
#include "SFML\Graphics.hpp"
#include "ExitButton.h"
#include <iostream>

ExitButton::ExitButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{
	_window = aWindow;
}

void ExitButton::OnClick()
{
	std::cout << "Exit" << std::endl;
	_window->close();
}