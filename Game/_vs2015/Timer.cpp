#include "Timer.h"
#include "mge/behaviours/AbstractBehaviour.hpp"

Timer::Timer(std::function<void(float)> onTick, std::function<void()> onEnd, float time, bool reoccurring) : AbstractBehaviour("Timer")
{
	t = 0;
	_onTick = onTick;
	_onEnd = onEnd;
	_time = time;
	_reoc = reoccurring;
	_paused = true;
}

Timer::~Timer()
{
	AbstractBehaviour::~AbstractBehaviour();
}

void Timer::Start()
{
	_paused = false;
}

void Timer::Pause()
{
	_paused = true;
}

bool Timer::IsStarted()
{
	return !_paused;
}

void Timer::Reset(bool immediateStart)
{
	_paused = !immediateStart;
	t = 0;
}

float Timer::GetCurrentTime()
{
	return t;
}

void Timer::update(float pTime)
{
	if (_paused)return;
	t += pTime;
	if (t >= _time)
	{
		Pause();
		if (_reoc)
		{
			Reset(true);
			
		}
		OnEnd();
	}
	else
	{
		OnTick(t);
	}
}

void Timer::OnTick(float time)
{
	if (_onTick != nullptr) _onTick(time);
}

void Timer::OnEnd()
{
	_onEnd();
}

float Timer::GetProgress()
{
	return t / _time;
}

AbstractBehaviour* Timer::Clone()
{
	return (AbstractBehaviour*)new Timer(_onTick, _onEnd, _time, _reoc);
}