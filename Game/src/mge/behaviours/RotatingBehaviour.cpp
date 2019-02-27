#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"

RotatingBehaviour::RotatingBehaviour():AbstractBehaviour("RotatingBehaviour")
{
	//ctor
}

RotatingBehaviour::~RotatingBehaviour()
{
	//dtor
}

AbstractBehaviour* RotatingBehaviour::Clone()
{
	return new RotatingBehaviour();
}

void RotatingBehaviour::update(float pStep)
{
    //rotates 45° per second
	_owner->rotate(pStep * glm::radians(45.0f), glm::vec3( 0.0f, 1.0f, 0.0f ) );
}
