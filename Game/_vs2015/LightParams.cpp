#include "LightParams.hpp"

LightParams::LightParams(int type, float intensity, glm::vec2 attenuation,
	glm::vec3 color, glm::vec3 ambientColor)
{

	this->type = type;
	this->intensity = intensity;
	this->attenuation = attenuation;
	this->color = color;
	this->ambientColor = ambientColor;
}