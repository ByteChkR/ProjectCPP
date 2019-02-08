#ifndef HUDSPRITE_H
#define HUDSPRITE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class HudSprite 
{

	public:
		HudSprite(std::string filename);
		sf::Sprite sprite;

	private:
		sf::Texture _texture;


};

#endif // HUDSPRITE_HPP
