#include "mge/behaviours/AbstractBehaviour.hpp"
#include "CheckpointTrigger.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "ParticleEmitter.h"

bool CheckpointTrigger::_fire = false;

CheckpointTrigger::CheckpointTrigger(int particleBurstCount, ParticleEmitter* pem)
{
	_pem = pem;
	_pbc = particleBurstCount;
}

CheckpointTrigger::~CheckpointTrigger()
{

}

void CheckpointTrigger::OnCollision(GameObject* other)
{
	_current = true;
}

void CheckpointTrigger::update(float pTime)
{
	if (_fire && !_current)_pem->StartBurst(_pbc);
	else
	{
		_current = false;
		_pem->Stop();
	}
}

AbstractBehaviour* CheckpointTrigger::Clone()
{
	return new CheckpointTrigger(_pbc, _pem);
}
