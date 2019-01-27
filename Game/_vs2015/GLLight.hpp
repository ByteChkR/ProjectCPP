#ifndef GLLIGHT_HPP
#define GLLIGHT_HPP

#include "glm.hpp"
#include "GL/glew.h"
#include "LightParams.hpp"
struct GLLight
{
public:
	GLLight();
	GLLight(GLint type, GLint intensity, GLint attenuation, GLint position, GLint color, GLint ambientColor);
	GLint _type, _intensity, _attenuation, _position, _color, _ambientColor;
	void SetLight(LightParams* params);
};

#endif // !GLLIGHT_HPP
