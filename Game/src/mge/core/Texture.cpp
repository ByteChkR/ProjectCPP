#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "mge/core/Texture.hpp"
#include "mge/core/AbstractGame.hpp"
#include "../_vs2015/Debug.h"

Texture::Texture() : _id() {
	glGenTextures(1, &_id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}

GLuint Texture::getId() {
	return _id;
}

// importer for textures
Texture* Texture::load(const std::string& pFilename, bool useFallback, bool wrapMirrored)
{
	// load from file and store in cache
	sf::Image image;
	if (image.loadFromFile(pFilename)) {
		//normal image 0,0 is top left, but opengl considers 0,0 to be bottom left, so we flip the image internally
		image.flipVertically();
		//create a wrapper for the id (texture is nothing more than that) and
		//load corresponding data into opengl using this id
		Texture * texture = new Texture();
		glBindTexture(GL_TEXTURE_2D, texture->getId());
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (wrapMirrored)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}
	else {
		if (useFallback)
		{
			Debug::LogError("Using Fallback Texture instead of: " + pFilename);
		}
		else 
		{
			Debug::LogError("Returning NULLPTR because useFallback is set to false");
		}
		return useFallback ? _loadFromSFImage(AbstractGame::instance->fallbackTexture, wrapMirrored) : nullptr;
	}
}

Texture* Texture::_loadFromSFImage(sf::Image* image, bool wrapMirrored)
{
	//normal image 0,0 is top left, but opengl considers 0,0 to be bottom left, so we flip the image internally
	image->flipVertically();
	//create a wrapper for the id (texture is nothing more than that) and
	//load corresponding data into opengl using this id
	Texture * texture = new Texture();
	glBindTexture(GL_TEXTURE_2D, texture->getId());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getSize().x, image->getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (wrapMirrored)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}










