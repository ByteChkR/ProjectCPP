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
	return _owner->getLocalPosition();
}

DynamicBoxCollider::~DynamicBoxCollider()
{

}

void DynamicBoxCollider::OnCollision(GameObject* other)
{

}

void DynamicBoxCollider::update(float pTime)
{

}