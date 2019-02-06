#ifndef ABSTRACTSTATICCOLLIDER_HPP
#define ABSTRACTSTATICCOLLIDER_HPP

#include "DynamicBoxCollider.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

class AbstractStaticCollider : public AbstractBehaviour
{
public:
	AbstractStaticCollider();
	virtual ~AbstractStaticCollider() = 0;
	virtual bool IsCollision(DynamicBoxCollider* ball) = 0;
	GameObject* GetOwner();


};

#endif // !ABSTRACTSTATICCOLLIDER_HPP
