#include "StaticSphereCollider.hpp"

StaticSphereCollider::StaticSphereCollider(float radius)
{
	_radius = radius;
	_owner = nullptr;
}

bool StaticSphereCollider::IsCollision(DynamicBoxCollider ball)
{
	if (_owner == nullptr)return false;

	if (glm::distance(ball.GetPosition(), _owner->getLocalPosition()) < _radius + ball.GetRadius())
	{
		//Collision
		return true;
	}
	return false;
}