#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/AbstractGame.hpp"
RotatingBehaviour::RotatingBehaviour(float pIntensity, float pFloatingIntensity) :AbstractBehaviour("RotatingBehaviour")
{
	_intensity = pIntensity;
	totalTime = 0;
	_floatingIntensity = pFloatingIntensity;
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
		_initYPos = _owner->getLocalPosition().y;
	}
	totalTime += pStep;
	//rotates 45° per second
	_owner->rotate(pStep * glm::radians(45.0f*_intensity), glm::vec3(0.0f, 1.0f, 0.0f));
	float sinus = glm::sin(totalTime * 5);
	_owner->setLocalPosition(glm::vec3(_owner->getLocalPosition().x, _initYPos + 0.25 + sinus *_floatingIntensity, _owner->getLocalPosition().z));

}
