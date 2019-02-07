#include "AbstractBehaviour.hpp"
#include <string>

AbstractBehaviour::AbstractBehaviour(std::string name):_owner(nullptr), _name(name) {}

AbstractBehaviour::~AbstractBehaviour()
{
	_owner = nullptr;
}

void AbstractBehaviour::setOwner (GameObject* pOwner) {
    _owner = pOwner;
}

GameObject* AbstractBehaviour::getOwner() {
	return _owner;
}

void AbstractBehaviour::OnCollision(GameObject* other)
{

}

AbstractBehaviour* AbstractBehaviour::Clone()
{
	return nullptr;
}

std::string AbstractBehaviour::GetName()
{
	return _name;
}

