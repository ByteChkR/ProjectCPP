#include <cassert>
#include <iostream>

#include <string>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "mge/config.hpp"
#include "HudSprite.h"

HudSprite::HudSprite(std::string filename): _texture(), sprite()
{
	if (!_texture.loadFromFile(config::MGE_TEXTURE_PATH + filename)) {
		std::cout << "Could not load texture, exiting..." << std::endl;
		return;
	}

	sprite.setTexture(_texture);

}
