#ifndef STATICBOXCOLLIDER_HPP
#define STATICBOXCOLLIDER_HPP

#include "glm.hpp"
#include "AbstractStaticCollider.hpp"	

class StaticBoxCollider : public AbstractStaticCollider
{
public:
	StaticBoxCollider(glm::vec3 Min, glm::vec3 Max);
	~StaticBoxCollider();
	virtual void update(float pTime) override;
	virtual AbstractBehaviour* Clone() override;
	virtual void OwnerChanged(GameObject* owner) override;
	virtual bool IsCollision(DynamicBoxCollider* ball) override;
	std::vector<glm::vec3> GetBounds();
private:
	bool _init;
	glm::vec3 min;
	glm::vec3 max;
};


#endif // !STATICBOXCOLLIDER
