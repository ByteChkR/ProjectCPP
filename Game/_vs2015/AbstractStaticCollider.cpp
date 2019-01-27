#include "AbstractStaticCollider.hpp"

AbstractStaticCollider::AbstractStaticCollider() { _owner = nullptr; }
AbstractStaticCollider::~AbstractStaticCollider(){}

void AbstractStaticCollider::SetOwner(GameObject* owner)
{
	_owner = owner;
}