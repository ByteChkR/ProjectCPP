#ifndef TURKEYCAGE_HPP
#define TURKEYCAGE_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Simply rotates the object around its origin with a fixed speed.
 */
class TurkeyCage : public AbstractBehaviour
{
public:
	TurkeyCage();
	virtual ~TurkeyCage();
	virtual AbstractBehaviour* Clone();
	virtual void update(float pStep);

};

#endif
