#ifndef ROTATINGBEHAVIOUR_HPP
#define ROTATINGBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class RotatingBehaviour : public AbstractBehaviour
{
	public:
		RotatingBehaviour();
		virtual ~RotatingBehaviour();
		virtual AbstractBehaviour* Clone();
		virtual void update(float pStep);
		
		float totalTime;
		bool init;
		float _initYPos;
};

#endif // ROTATINGBEHAVIOUR_HPP
