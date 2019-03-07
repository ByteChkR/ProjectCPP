#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"

RotatingBehaviour::RotatingBehaviour(float pIntensity):AbstractBehaviour("RotatingBehaviour")
{
	_intensity = pIntensity;
	totalTime = 0;
	init = false;
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
	if (!init)
	{
		init = true;
		
	}
	totalTime += pStep;
    //rotates 45° per second
	_owner->rotate(pStep * glm::radians(45.0f*_intensity), glm::vec3( 0.0f, 1.0f, 0.0f ) );
	_owner->setLocalPosition(_owner->getLocalPosition() + glm::vec3(0, glm::sin(totalTime*10)/30, 0));

}
