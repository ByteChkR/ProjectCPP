#include "HudText.h"
#include <iostream>
#include "../_vs2015/Debug.h"
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "mge/config.hpp"

HudText::HudText(std::string filename, int fontSize, sf::Color color) : _font(), _text(), _textInfo()
{
	if (!_font.loadFromFile(config::MGE_FONT_PATH + filename)) {
		Debug::LogError("Could not load font, exiting...");
		return;
	}
	_text.setString("");
	_text.setFont(_font);
	_text.setCharacterSize(fontSize);
	_text.setFillColor(color);

}
