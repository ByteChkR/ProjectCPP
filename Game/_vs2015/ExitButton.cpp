#include "Button.h"
#include "SFML\Graphics.hpp"
#include "ExitButton.h"
#include <iostream>

ExitButton::ExitButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void ExitButton::OnClick()
{
	std::cout << "Exit" << std::endl;
	system("rundll32.exe powrprof.dll,SetSuspendState 0,1,0");
}