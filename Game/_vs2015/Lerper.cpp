#include "Lerper.h"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "Timer.h"
#include <string>

Lerper::Lerper(std::function<void(float)> onTick, std::function<void()> onEnd, float time, std::string name, bool reocurring):Timer(onTick, onEnd,time, name, reocurring)
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