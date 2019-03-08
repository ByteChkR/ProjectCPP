#ifndef LIGHTPARAMS_HPP
#define LIGHTPARAMS_HPP

#include "glm.hpp"
#include <string>


struct LightParams
{
public:
	LightParams(int type = 0, float intensity = 1, glm::vec2 attenuation = glm::vec2(0),
		glm::vec3 color = glm::vec3(1,1,1), glm::vec3 ambientColor = glm::vec3(0.01f));
	LightParams(std::string lightParamFile);
	int type;
	float intensity;
	glm::vec2 attenuation;
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 ambientColor;
	glm::vec3 forward;
};

#endif // !LIGHTPARAMS_HPP
