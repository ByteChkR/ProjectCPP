#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "mge/core/Texture.hpp"
#include <string>
class Texture;
struct Material
{
public:
	Material(std::string path = "");
	~Material();

	float shininess;
	float maxHeight;
	Texture* diffuse = nullptr;
	
	Texture* normal = nullptr;
	Texture* specular = nullptr;
	Texture* height = nullptr;


};

#endif // !MATERIAL_HPP
