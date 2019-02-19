#include "DynamicBoxCollider.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "CollisionManager.hpp"
#include "mge/core/AbstractGame.hpp"
#include "glm.hpp"

DynamicBoxCollider::DynamicBoxCollider(glm::vec3 Min, glm::vec3 Max) : AbstractBehaviour("DBoxCollider")
{
	min = Min;
	max = Max;
	AbstractGame::instance->_manager->RegisterDynamic(this);
}

AbstractBehaviour* DynamicBoxCollider::Clone()
{
	return new DynamicBoxCollider(min, max);
}

glm::vec3 DynamicBoxCollider::GetMax()
{
	return max;
}

glm::vec3 DynamicBoxCollider::GetMin()
{
	return min;
}

void DynamicBoxCollider::FireCollision(GameObject* other)
{
	_owner->FireCollision(other); //Pass through Gameobject to call all behaviours
}

glm::vec3 DynamicBoxCollider::GetPosition()
{
	return _owner->getWorldPosition();
}

DynamicBoxCollider::~DynamicBoxCollider()
{
	AbstractGame::instance->_manager->UnRegisterDynamic(this);
}

void DynamicBoxCollider::OnCollision(GameObject* other)
{

}

void DynamicBoxCollider::update(float pTime)
{

}
