#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <map>
#include <string>
#include "SFML/Graphics.hpp"
#include <GL/glew.h>

class Texture
{
	public:
		static Texture* load(const std::string& pTexturePath, bool useFallback = true, bool wrapMirrored = false);
		virtual ~Texture();
		GLuint getId();

	protected:
	    Texture();
		static Texture* _loadFromSFImage(sf::Image* image, bool wrapMirrored = false);
        static Texture* _loadFromFile(const std::string pTexturePath);

	    //OpenGL id for texture buffer
		GLuint _id;
};

#endif // TEXTURE_HPP
