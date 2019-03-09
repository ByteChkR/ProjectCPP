#ifndef ROTATINGBEHAVIOUR_HPP
#define ROTATINGBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class RotatingBehaviour : public AbstractBehaviour
{
	public:
		RotatingBehaviour(float pIntensity = 1, float pFloatingIntensity = 1, glm::vec3 rotationAxis = glm::vec3(0, 1, 0));
		virtual ~RotatingBehaviour();
		virtual AbstractBehaviour* Clone();
		virtual void update(float pStep);

		float _intensity = 1;
		float totalTime;
		bool init;
		float _floatingIntensity;
		float _initYPos;
		glm::vec3 rotationAxis;
};

#endif // ROTATINGBEHAVIOUR_HPP
