#ifndef DYNAMICSPHERECOLLIDER_HPP
#define DYNAMICSPHERECOLLIDER_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

class DynamicBoxCollider : public AbstractBehaviour
{
public:
	DynamicBoxCollider(glm::vec3 Min, glm::vec3 Max);
	virtual ~DynamicBoxCollider();

	virtual void update(float pStep);
	glm::vec3 GetPosition();
	glm::vec3 GetMin();
	glm::vec3 GetMax();
	virtual void OnCollision(GameObject* other) override;
	void FireCollision(GameObject* other);

private:
	glm::vec3 min;
	glm::vec3 max;
};

#endif // !DYNAMICSPHERECOLLIDER_HPP
