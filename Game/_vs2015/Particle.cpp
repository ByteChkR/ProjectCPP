#include "Particle.h"
#include "glm.hpp"

Particle::Particle() :position(0), velocity(0), acceleration(0), color(1), life(0), transparencyPerSecond(0), transparencyStart(1), gravity(1)
{

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
	p->transparencyStart = transparencyStart;
	p->velocity = velocity;
	return p;
}