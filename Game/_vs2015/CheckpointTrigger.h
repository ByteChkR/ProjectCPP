#ifndef CHECKPOINTTRIGGER_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "ParticleEmitter.h"

class CheckpointTrigger : public AbstractBehaviour
{
public:
	CheckpointTrigger(int particleBurstCount , ParticleEmitter* pem);
	virtual ~CheckpointTrigger();
	virtual void update(float pTime) override;
	virtual AbstractBehaviour* Clone() override;
	virtual void OnCollision(GameObject* other) override;
	static bool _fire;
private:
	ParticleEmitter* _pem;
	int _pbc;
	bool _current;
};


#endif // !CHECKPOINTTRIGGER_HPP
