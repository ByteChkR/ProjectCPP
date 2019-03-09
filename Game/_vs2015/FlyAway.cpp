#include "FlyAway.h"
#include "mge/core/GameObject.hpp"
#include "glm.hpp"
#include "mge/core/AbstractGame.hpp"
FlyAway::FlyAway()
{
	_maxReleaseTime = 5;
	_curReleaseTime = 0;
	_isActive = false;
	_velocity = glm::vec3(0);
}

FlyAway::~FlyAway()
{
	AbstractBehaviour::~AbstractBehaviour();
}

void FlyAway::update(float pStep)
{
	if (!_isActive)return;

	_curReleaseTime += pStep;
	if (_curReleaseTime >= _maxReleaseTime)
	{
		Reset();
		return;
	}

	_owner->setLocalPosition(_owner->getLocalPosition() + _velocity * pStep);
}

void FlyAway::Release(glm::vec3 position)
{
	_isActive = true;
	_owner->EnableBehaviours();
	_owner->setLocalPosition(position);
	_velocity = glm::vec3(-2, 3, 1);
	if (glm::mod((int)AbstractGame::instance->GetTimeSinceStartup(), 2) == 1) _velocity = glm::vec3(2, 3, 1);

}

void FlyAway::Reset()
{
	_isActive = false;
	_curReleaseTime = 0;
	_owner->DisableBehaviours();

}