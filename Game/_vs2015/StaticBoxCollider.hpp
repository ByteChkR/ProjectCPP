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
	void AddOffset(glm::vec3 addition);
	void SetOffset(glm::vec3 offset);
	glm::vec3 GetOffset();
	std::vector<glm::vec3> GetBounds();
	glm::vec3 GetDimensions();
private:
	bool _init;
	glm::vec3 offset;
	glm::vec3 min;
	glm::vec3 max;
};


#endif // !STATICBOXCOLLIDER
