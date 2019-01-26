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

std::string AbstractBehaviour::GetName()
{
	return _name;
}

