#ifndef DYNAMICSPHERECOLLIDER_HPP
#define DYNAMICSPHERECOLLIDER_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"

class DynamicSphereCollider
{
public:
	DynamicSphereCollider(float radius, float mass, float friction, float gravity);
	void SetVelocity(glm::vec3 newVelocity);
	void SetAcceleration(glm::vec3 newAcceleration);
	void AddAcceleration(glm::vec3 acceleration);
	void Update(float pTime);
	void SetOwner(GameObject* owner);
	glm::vec3 GetPosition();
	float GetRadius();

private:
	GameObject* _owner;
	float _radius;
	float _mass;
	float _friction;
	float _gravity;
	glm::vec3 _velocity;
	glm::vec3 _acceleration;
};

#endif // !DYNAMICSPHERECOLLIDER_HPP
