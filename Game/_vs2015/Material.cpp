#include "Material.hpp"

Material::Material(std::string path)
{
	
	//Load From filee
}

Material::~Material()
{
	if (diffuse != nullptr)
		diffuse->~Texture();
	if (normal != nullptr)
		normal->~Texture();
	if (specular != nullptr)
		specular->~Texture();
	if (height != nullptr)
		height->~Texture();
}