#ifndef STATICBOXCOLLIDER_HPP
#define STATICBOXCOLLIDER_HPP

#include "glm.hpp"
#include "AbstractStaticCollider.hpp"	

class StaticBoxCollider : public AbstractStaticCollider
{
public:
	StaticBoxCollider(float width, float height, float depth);
	~StaticBoxCollider();
	virtual void update(float pTime) override;
	virtual bool IsCollision(DynamicBoxCollider* ball) override;
private:
	float _width;
	float _height;
	float _depth;
};


#endif // !STATICBOXCOLLIDER
