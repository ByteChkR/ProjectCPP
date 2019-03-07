#ifndef PARTICLE_HPP

#define PARTICLE_HPP


#include "glm.hpp"


class Particle
{
public:

	Particle* Clone();
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec4 color;
	float transparencyPerSecond;
	float transparencyStart;
	float life;
	float gravity;
	Particle();
};

#endif // !PARTICLE_HPP
