#include "AbstractBehaviour.hpp"
#include <string>

AbstractBehaviour::AbstractBehaviour(std::string name):_owner(nullptr), _name(name), _enabled(true) {}

AbstractBehaviour::~AbstractBehaviour()
{
	_owner = nullptr;
}

void AbstractBehaviour::setOwner(GameObject* pOwner) {
	_owner = pOwner;
	OwnerChanged();
}

void AbstractBehaviour::OwnerChanged() {}

void AbstractBehaviour::enable() { _enabled = true; }
void AbstractBehaviour::disable() { _enabled = false; }
bool AbstractBehaviour::IsEnabled() { return _enabled; }


GameObject* AbstractBehaviour::getOwner() {
	return _owner;
}

void AbstractBehaviour::OnCollision(GameObject* other)
{

}

std::string AbstractBehaviour::GetName()
{
	return _name;
}

