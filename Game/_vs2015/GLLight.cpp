#include "GLLight.hpp"
#include "LightParams.hpp"
#include "GL/glew.h"

GLLight::GLLight(GLint type, GLint intensity, GLint attenuation, GLint position, GLint color, GLint ambientColor)
{
	_type = type;
	_intensity = intensity;
	_attenuation = attenuation;
	_position = position;
	_color = color;
	_ambientColor = ambientColor;
}

GLLight::GLLight() {};

void GLLight::SetLight(LightParams* params)
{
	glUniform1i(_type, params->type);
	glUniform1f(_intensity, params->intensity);
	glUniform2f(_attenuation, params->attenuation.x, params->attenuation.y);
	glUniform3f(_position, params->position.x, params->position.y, params->position.z);
	glUniform3f(_color, params->color.x, params->color.y, params->color.z);
	glUniform3f(_ambientColor, params->ambientColor.x, params->ambientColor.y, params->ambientColor.z);

}