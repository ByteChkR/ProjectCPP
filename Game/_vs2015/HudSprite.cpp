#include <cassert>
#include <iostream>

#include <string>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "mge/config.hpp"
#include "HudSprite.h"

HudSprite::HudSprite(std::string filename,float scale): _texture(), sprite()
{
	if (!_texture.loadFromFile(config::MGE_TEXTURE_PATH + filename)) {
		std::cout << "Could not load texture, exiting..." << std::endl;
		return;
	}
	
	sprite.setTexture(_texture);
	sprite.setOrigin(_texture.getSize().x/2, _texture.getSize().y / 2);

	scaledSprite.setTexture(_texture);
	scaledSprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
	scaledSprite.setScale(scale,scale);
}
