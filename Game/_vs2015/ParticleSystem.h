#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>
#include "ParticleEmitter.h"

class ParticleSystem
{
public:
	ParticleSystem();
	static ParticleSystem* instance;
	void RegisterParticleEmitter(ParticleEmitter* em);
	void UnregisterParticleEmitter(ParticleEmitter* em);
	void Update(float pTime);

private:
	std::vector<ParticleEmitter*> _emitters;
};


#endif // !PARTICLESYSTEM_HPP
