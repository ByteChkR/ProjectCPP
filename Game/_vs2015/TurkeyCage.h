#ifndef TURKEYCAGE_HPP
#define TURKEYCAGE_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "FlyAway.h"
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
	void Release();

	static FlyAway* turkey;
private:

	void InitializeTurkey();
};

#endif
