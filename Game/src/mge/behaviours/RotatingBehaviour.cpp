#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/AbstractGame.hpp"
RotatingBehaviour::RotatingBehaviour(float pIntensity, float pFloatingIntensity, glm::vec3 rotationAxis) :AbstractBehaviour("RotatingBehaviour")
{
	_intensity = pIntensity;
	totalTime = 0;
	_floatingIntensity = pFloatingIntensity;
	init = false;
	this->rotationAxis = rotationAxis;
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
	_owner->rotate(pStep * glm::radians(45.0f*_intensity), rotationAxis);
	float sinus = glm::sin(totalTime * 5);
	_owner->setLocalPosition(glm::vec3(_owner->getLocalPosition().x, _initYPos + 0.25 + sinus *_floatingIntensity, _owner->getLocalPosition().z));

}
