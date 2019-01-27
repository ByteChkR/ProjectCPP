#include "Material.hpp"

Material::Material(std::string path)
{
	//Load From filee
}

Material::~Material()
{
	diffuse->~Texture();
	normal->~Texture();
	specular->~Texture();
	height->~Texture();
}