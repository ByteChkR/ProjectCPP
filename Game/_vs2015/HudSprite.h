#ifndef HUDSPRITE_H
#define HUDSPRITE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class HudSprite 
{

	public:
		HudSprite(std::string filename,float scale = 1);
		sf::Sprite sprite;
		sf::Sprite scaledSprite;

	private:
		sf::Texture _texture;


};

#endif // HUDSPRITE_HPP
