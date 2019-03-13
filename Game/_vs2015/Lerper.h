#ifndef LERPER_HPP

#define LERPER_HPP
#include "Timer.h"
#include <functional>
#include "mge/behaviours/AbstractBehaviour.hpp"
class Lerper : public Timer
{
	public:
	Lerper(std::function<void(float)> onTick, std::function<void()> onEnd, float time, std::string name = "Lerper", bool reocurring = false);
	virtual ~Lerper() override;

	virtual void OnTick(float time)override;

};

#endif // 
