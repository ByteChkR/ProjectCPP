#include "Lerper.h"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "Timer.h"

Lerper::Lerper(std::function<void(float)> onTick, std::function<void()> onEnd, float time, bool reocurring):Timer(onTick, onEnd,time, reocurring)
{

}

Lerper::~Lerper()
{
	Timer::~Timer();
}

void Lerper::OnTick(float time)
{
	Timer::OnTick(GetProgress());
}