#ifndef FLYAWAY_HPP
#define FLYAWAY_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"

class FlyAway : public AbstractBehaviour
{
public:
	FlyAway();
	virtual ~FlyAway() override;
	virtual void update(float pStep) override;
	void Release(glm::vec3 position);
private:
	float _maxReleaseTime;
	bool _isActive;
	float _curReleaseTime;
	void Reset();
	glm::vec3 _velocity;
};

#endif // 
