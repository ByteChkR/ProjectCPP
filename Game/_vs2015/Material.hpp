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
	Texture* diffuse;
	
	Texture* normal;
	Texture* specular;
	Texture* height;


};

#endif // !MATERIAL_HPP
