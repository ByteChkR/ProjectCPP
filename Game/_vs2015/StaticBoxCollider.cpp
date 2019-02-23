#include "StaticBoxCollider.hpp"
#include "DynamicBoxCollider.hpp"
#include "CollisionManager.hpp"
#include "mge/core/AbstractGame.hpp"

StaticBoxCollider::StaticBoxCollider(glm::vec3 Min, glm::vec3 Max) : AbstractStaticCollider()
{
	_name = "BOXCOLLIDER";
	min = Min;
	max = Max;

	_init = false;
}


StaticBoxCollider::~StaticBoxCollider()
{

	AbstractGame::instance->_manager->UnRegisterCollider(this);
}

std::vector<glm::vec3> StaticBoxCollider::GetBounds()
{
	std::vector<glm::vec3> ret = std::vector<glm::vec3>();
	//BackPlane
	ret.push_back(max);
	ret.push_back(glm::vec3(min.x, max.y, max.z));
	ret.push_back(glm::vec3(min.x, min.y, max.z));
	ret.push_back(glm::vec3(max.x, min.y, max.z));


	ret.push_back(max);

	//FrontPlane
	ret.push_back(glm::vec3(max.x, max.y, min.z));
	ret.push_back(glm::vec3(min.x, max.y, min.z));
	ret.push_back(min);
	ret.push_back(glm::vec3(max.x, min.y, min.z));


	ret.push_back(glm::vec3(max.x, max.y, min.z));
	ret.push_back(glm::vec3(max.x, min.y, min.z));
	ret.push_back(glm::vec3(max.x, min.y, max.z));
	ret.push_back(glm::vec3(min.x, min.y, max.z));
	ret.push_back(min);
	ret.push_back(glm::vec3(min.x, max.y, min.z));
	ret.push_back(glm::vec3(min.x, max.y, max.z));

	return ret;
}

AbstractBehaviour* StaticBoxCollider::Clone()
{
	return new StaticBoxCollider(min, max);
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

	if (pos.x + this->min.x >= ballPos.x + max.x)return false;
	if (pos.x + this->max.x <= ballPos.x + min.x)return false;
	if (pos.y + this->min.y >= ballPos.y + max.y)return false;
	if (pos.y + this->max.y <= ballPos.y + min.y)return false;
	if (pos.z + this->min.z >= ballPos.z + max.z)return false;
	if (pos.z + this->max.z <= ballPos.z + min.z)return false;

	return true;
}