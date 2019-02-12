#include "StaticBoxCollider.hpp"
#include "DynamicBoxCollider.hpp"
#include "CollisionManager.hpp"
#include "mge/core/AbstractGame.hpp"

StaticBoxCollider::StaticBoxCollider(float width, float height, float depth) : AbstractStaticCollider()
{
	_name = "BOXCOLLIDER";
	_height = height;
	_width = width;
	_depth = depth;
	_init = false;
}

StaticBoxCollider::StaticBoxCollider(glm::vec3 dims) :StaticBoxCollider(dims.x, dims.y, dims.z) {}
StaticBoxCollider::~StaticBoxCollider()
{

}

AbstractBehaviour* StaticBoxCollider::Clone()
{
	return new StaticBoxCollider(_width, _height, _depth);
}

void StaticBoxCollider::update(float time)
{
	if (!_init && _owner != nullptr)
	{
		_init = true;
		AbstractGame::instance->_manager->RegisterCollider(this);
	}
	else if (_init && _owner == nullptr)
	{
		_init = false;
		AbstractGame::instance->_manager->UnRegisterCollider(this);
	}
}

void StaticBoxCollider::OwnerChanged(GameObject* newOwner)
{

}

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