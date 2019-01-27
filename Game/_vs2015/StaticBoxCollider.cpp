#include "StaticBoxCollider.hpp"

StaticBoxCollider::StaticBoxCollider(float width, float height, float depth)
{
	_height = height;
	_width = width;
	_depth = depth;
}

bool StaticBoxCollider::IsCollision(DynamicSphereCollider ball)
{
	if (_owner == nullptr)return false;
	glm::vec3 pos = _owner->getLocalPosition();

	if (pos.x - _width/2 > ball.GetPosition().x + ball.GetRadius())return false;
	if (pos.x + _width/2 < ball.GetPosition().x - ball.GetRadius())return false;
	if (pos.y - _height / 2 > ball.GetPosition().y + ball.GetRadius())return false;
	if (pos.y + _height / 2 > ball.GetPosition().y - ball.GetRadius())return false;
	if (pos.z - _depth / 2 > ball.GetPosition().z + ball.GetRadius())return false;
	if (pos.z + _depth / 2 > ball.GetPosition().z - ball.GetRadius())return false;

	return true;
}