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
	glm::vec3 randomizeAcceleration;
	float transparencyPerSecond;
	float transparencyStart;
	float life;
	float gravity;
	Particle(glm::vec3 randomizeAcceleration = glm::vec3(1, 0, 1), glm::vec3 position = glm::vec3(0), glm::vec3 velocity = glm::vec3(0),
		glm::vec3 acceleration = glm::vec3(0), glm::vec4 color = glm::vec4(1),
		float life = 1, float transparencyPerSecond = 0, float transparencyStart = 1, float gravity = 0);
};

#endif // !PARTICLE_HPP
