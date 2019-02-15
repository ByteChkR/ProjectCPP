#ifndef PARTICLEEMITTER_HPP
#define PARTICLEEMITTER_HPP

#include "Particle.h"
#include "glm.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "ObjectPool.hpp"
#include "mge/core/ShaderProgram.hpp"
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include "mge/core/Texture.hpp"
class ParticleEmitter : AbstractMaterial
{
public:
	ParticleEmitter(Particle* original, Texture* particleTexture, int maxParticles = 500);
	//void SetParticleLifetime(float maxTime);
	//void SetParticleStartPosition(glm::vec3 startPosition);
	//void SetParticleStartColor(glm::vec4 startColor);
	//void SetParticleEndColor(glm::vec4 endColor);
	//void SetParticleStartPositionRandomization(bool enabled, float maxOffset);
	//void SetParticleStartVelocityRandomization(bool enabled, float maxOffset);
	//void SetParticleLifeTimeRandomization(bool enabled, float maxOffset);
	void Start();
	void Stop(bool immediate = false);

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pPerspectiveMatrix) override;
	void UpdateParticles(float pTime);
	void SpawnParticles(int amount);
	bool IsEnabled();
	
private:
	int _maxParticles;
	bool _isEnabled;
	bool _stopProduce;

	
	
	
	static ShaderProgram* _shader;
	static GLint _uMMatrix;
	static GLint _uPMatrix;
	static GLint _uVMatrix;
	static GLint _aNormal;
	static GLint _aVertex;
	static GLint _aUV;
	static GLint _offset;
	static GLint _color;
	static GLint _texture;
	Texture* _particleTexture;
	std::vector<Particle*> _activeParticles;
	unsigned seed = unsigned(std::chrono::system_clock::now().time_since_epoch().count());
	static std::default_random_engine e;
	static void _initializeShader();
	Particle* _original;
	ObjectPool<Particle*>* _pool;
};

#endif // !PARTICLEEMITTER_HPP
