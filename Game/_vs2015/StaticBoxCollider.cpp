#include "StaticBoxCollider.hpp"
#include "DynamicBoxCollider.hpp"
#include "CollisionManager.hpp"
#include "mge/core/AbstractGame.hpp"

StaticBoxCollider::StaticBoxCollider(float width, float height, float depth) : AbstractStaticCollider()
{
	_height = height;
	_width = width;
	_depth = depth;
	AbstractGame::instance->_manager->RegisterCollider(this);
}

StaticBoxCollider::~StaticBoxCollider()
{

}

void StaticBoxCollider::update(float time){}

bool StaticBoxCollider::IsCollision(DynamicBoxCollider* ball)
{
	if (_owner == nullptr)return false;
	glm::vec3 pos = _owner->getWorldPosition();
	glm::vec3 min, max;
	min = ball->GetMin();
	max = ball->GetMax();
	glm::vec3 ballPos = ball->GetPosition();

	if (pos.x - _width / 2 > ballPos.x + max.x)return false;
	if (pos.x + _width / 2 < ballPos.x + min.x)return false;
	if (pos.y - _height / 2 > ballPos.y + max.y)return false;
	if (pos.y + _height / 2 < ballPos.y + min.y)return false;
	if (pos.z - _depth / 2 > ballPos.z + max.z)return false;
	if (pos.z + _depth / 2 < ballPos.z + max.z)return false;

	return true;
}