#pragma once
#ifndef HUDSTEXT_H
#define HUDSText_H

#include <SFML/Graphics.hpp>
#include <iostream>

class HudText
{
	public:
		HudText(std::string filename = "arial.ttf", int fontSize = 16, sf::Color color = sf::Color::White);

		sf::Text _text;
	private:
		std::string _textInfo;

		sf::Font _font;
};


#endif