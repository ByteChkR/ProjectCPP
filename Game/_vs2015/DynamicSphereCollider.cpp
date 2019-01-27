#include "DynamicSphereCollider.hpp"

DynamicSphereCollider::DynamicSphereCollider(float radius, float mass, float friction, float gravity)
{
	_radius = radius;
	_mass = mass;
	_friction = friction;
	_gravity = gravity;
	_velocity = glm::vec3(0);
	_acceleration = glm::vec3(0);
	_owner = nullptr;
}

void DynamicSphereCollider::SetVelocity(glm::vec3 newVelocity)
{
	_velocity = newVelocity;
}

void DynamicSphereCollider::SetAcceleration(glm::vec3 newAcceleration)
{
	_acceleration = newAcceleration;
}

void DynamicSphereCollider::AddAcceleration(glm::vec3 acceleration)
{
	_acceleration += acceleration;
}

void DynamicSphereCollider::SetOwner(GameObject* owner)
{
	_owner = owner;

}

float DynamicSphereCollider::GetRadius()
{
	return _radius;
}

glm::vec3 DynamicSphereCollider::GetPosition()
{
	return _owner->getLocalPosition();
}

void DynamicSphereCollider::Update(float pTime)
{
	if (_owner == nullptr)return;
	_velocity += _acceleration*pTime;

	_velocity *= _friction;

	_owner->setLocalPosition(_owner->getLocalPosition() + _velocity);
}
