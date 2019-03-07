#include "ParticleSystem.h"

ParticleSystem* ParticleSystem::instance = nullptr;

ParticleSystem::ParticleSystem()
{
	instance = this;
}

void ParticleSystem::Update(float pTime)
{
	for (size_t i = 0; i < _emitters.size(); i++)
	{
		if(_emitters[i]->IsEnabled())
			_emitters[i]->UpdateParticles(pTime);

	}
}



void ParticleSystem::RegisterParticleEmitter(ParticleEmitter* em)
{
	_emitters.push_back(em);
}

void ParticleSystem::UnregisterParticleEmitter(ParticleEmitter* em)
{
	for (size_t i = 0; i < _emitters.size(); i++)
	{
		if (_emitters[i] == em)
		{
			_emitters.erase(_emitters.begin() + i);
			break;
		}
	}
}