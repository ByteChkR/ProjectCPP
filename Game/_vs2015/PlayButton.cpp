#include "Button.h"
#include "SFML\Graphics.hpp"
#include "PlayButton.h"
#include <iostream>

PlayButton::PlayButton(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite) : Button(aWindow, _buttonSprite)
{

}

void PlayButton::OnClick()
{
	std::cout << "Play" << std::endl;
}