#include "AbstractStaticCollider.hpp"

AbstractStaticCollider::AbstractStaticCollider() { _owner = nullptr; }
AbstractStaticCollider::~AbstractStaticCollider(){}

GameObject* AbstractStaticCollider::GetOwner()
{
	return _owner;
}