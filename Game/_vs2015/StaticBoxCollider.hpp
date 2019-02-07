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
	virtual AbstractBehaviour* Clone() override;
	virtual bool IsCollision(DynamicBoxCollider* ball) override;
private:
	bool _init;
	float _width;
	float _height;
	float _depth;
};


#endif // !STATICBOXCOLLIDER
