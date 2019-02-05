#ifndef STATICSPHERECOLLIDER_HPP
#define STATICSPHERECOLLIDER_HPP
#include "AbstractStaticCollider.hpp"

class StaticSphereCollider : public AbstractStaticCollider
{
public:
	StaticSphereCollider(float radius);
	virtual ~StaticSphereCollider() = 0;
	virtual bool IsCollision(DynamicBoxCollider ball) override;
private:
	float _radius;
};

#endif // !STATICSPHERECOLLIDER_HPP
