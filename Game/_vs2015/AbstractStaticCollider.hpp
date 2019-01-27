#ifndef ABSTRACTSTATICCOLLIDER_HPP
#define ABSTRACTSTATICCOLLIDER_HPP

#include "DynamicSphereCollider.hpp"

class AbstractStaticCollider
{
public:
	AbstractStaticCollider();
	virtual ~AbstractStaticCollider() = 0;
	virtual bool IsCollision(DynamicSphereCollider ball) = 0;
	void SetOwner(GameObject* owner);

protected:
	GameObject* _owner;

};

#endif // !ABSTRACTSTATICCOLLIDER_HPP
