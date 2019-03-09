#include "Particle.h"
#include "glm.hpp"

Particle::Particle(glm::vec3 randomizeAcceleration, glm::vec3 position /* = glm::vec3(0) */, glm::vec3 velocity /* = glm::vec3(0) */, 
	glm::vec3 acceleration /* = glm::vec3(0) */, glm::vec4 color /* = glm::vec4(1) */, 
	float life /* = 1 */, float transparencyPerSecond /* = 0 */, float transparencyStart /* = 1 */, float gravity /* = 0 */)
{	
	this->randomizeAcceleration = randomizeAcceleration;
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->color = color;
	this->life = life;
	this->transparencyPerSecond = transparencyPerSecond;
	this->transparencyStart = transparencyStart;
	this->gravity = gravity;
}

Particle* Particle::Clone()
{
	Particle* p = new Particle();
	p->color = color;
	p->gravity = gravity;
	p->acceleration = acceleration;
	p->life = life;
	p->position = position;
	p->transparencyPerSecond = transparencyPerSecond;
	p->randomizeAcceleration = randomizeAcceleration;
	p->transparencyStart = transparencyStart;
	p->velocity = velocity;
	return p;
}