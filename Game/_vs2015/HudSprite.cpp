#include <cassert>
#include <iostream>

#include <string>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "mge/config.hpp"
#include "HudSprite.h"
#include "../_vs2015/Debug.h"
HudSprite::HudSprite(std::string filename,float scale): _texture(), sprite()
{
	if (!_texture.loadFromFile(config::MGE_TEXTURE_PATH + filename)) {
		Debug::LogError("Could not load texture, exiting...");
		return;
	}
	
	sprite.setTexture(_texture);
	sprite.setOrigin(_texture.getSize().x/2.0f, _texture.getSize().y / 2.0f);

	scaledSprite.setTexture(_texture);
	scaledSprite.setOrigin(_texture.getSize().x / 2.0f, _texture.getSize().y / 2.0f);
	scaledSprite.setScale(scale,scale);
}
