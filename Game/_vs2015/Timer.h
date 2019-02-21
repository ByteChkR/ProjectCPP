#ifndef TIMER_HPP

#define TIMER_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include <functional>

class Timer : AbstractBehaviour
{
public:
	Timer(std::function<void(float)> onTick, std::function<void()> onEnd, float time, bool reocurring = false);
	virtual ~Timer() override;
	virtual void update(float pTime) override;
	virtual AbstractBehaviour* Clone() override;
	void Start();
	void Pause();
	void Reset(bool immediateStart = false);
	float GetCurrentTime();
	bool IsStarted();
private:
	std::function<void(float)> _onTick;
	std::function<void()> _onEnd;
	float _time;
	bool _reoc;
	float t;
	bool _paused;
};

#endif // !TIMER_HPP