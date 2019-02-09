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
	virtual void update(float pTime) =0;
	GameObject* GetOwner();
protected:
	virtual void OwnerChanged(GameObject* newOwner) = 0;

};

#endif // !ABSTRACTSTATICCOLLIDER_HPP
