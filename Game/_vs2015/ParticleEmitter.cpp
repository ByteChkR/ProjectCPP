#include "ParticleEmitter.h"
#include "Particle.h"
#include "glm.hpp"
#include "mge/core/Mesh.hpp"
#include <vector>
#include "mge/config.hpp"
#include "ParticleSystem.h"
#include <random>
#include "mge/core/Texture.hpp"
#include <chrono>
#include <iostream>

ShaderProgram* ParticleEmitter::_shader = nullptr;
GLint ParticleEmitter::_uMMatrix = 0;
GLint ParticleEmitter::_uPMatrix = 0;
GLint ParticleEmitter::_uVMatrix = 0;
GLint ParticleEmitter::_aUV = 0;
GLint ParticleEmitter::_aVertex = 0;
GLint ParticleEmitter::_aNormal = 0;
GLint ParticleEmitter::_color = 0;
GLint ParticleEmitter::_offset = 0;
GLint ParticleEmitter::_texture = 0;

std::default_random_engine ParticleEmitter::e;

ParticleEmitter::ParticleEmitter(Particle* original, Texture* particleTexture, int maxParticles)
{
	_particleTexture = particleTexture;
	e = std::default_random_engine(seed);
	ParticleSystem::instance->RegisterParticleEmitter(this);
	_original = original;
	_pool = new ObjectPool<Particle*>(_original);
	_maxParticles = maxParticles;
	_activeParticles = std::vector<Particle*>();
	_isEnabled = false;
	_stopProduce = false;

	_initializeShader();
}

bool ParticleEmitter::IsEnabled()
{
	return _isEnabled;
}

void ParticleEmitter::Start()
{
	if (_isEnabled)return;
	_isEnabled = true;
	_stopProduce = false;
}

void ParticleEmitter::Stop(bool immediate)
{
	if (!_isEnabled)return;
	if (!immediate)
	{
		_stopProduce = true;
	}
	else
	{
		_isEnabled = false;
		for (size_t i = 0; i < _activeParticles.size(); i++)
		{
			_pool->Give(_activeParticles[i]);

		}
		_activeParticles.clear();
	}
}

void ParticleEmitter::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pPerspectiveMatrix)
{

	_shader->use();
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glm::mat4 test = glm::mat4(1);
	test[3] = glm::vec4(pViewMatrix[3]);
	test = glm::rotate(test, glm::radians(90.0f), glm::vec3(1, 0, 0));


	glUniformMatrix4fv(_uPMatrix, 1, GL_FALSE, glm::value_ptr(pPerspectiveMatrix));
	glUniformMatrix4fv(_uVMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_uMMatrix, 1, GL_FALSE, glm::value_ptr(test));
	if (_particleTexture != nullptr || _texture == -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _particleTexture->getId());
		glUniform1i(_texture, 0);
	}

	for (size_t i = 0; i < _activeParticles.size(); i++)
	{
		if (_activeParticles[i]->life > 0.0f)
		{
			//Set Shader Attribs(pos/color)
			glUniform4f(_color, _activeParticles[i]->color.x, _activeParticles[i]->color.y, _activeParticles[i]->color.z, _activeParticles[i]->color.w);
			glUniform3f(_offset, _activeParticles[i]->position.x, _activeParticles[i]->position.y, _activeParticles[i]->position.z);
			//Render to opengl via mesh.streamtoopengl

			pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
		}
	}




	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void ParticleEmitter::UpdateParticles(float pTime)
{
	int maxParticlesPerStep = 2;
	int totalActive = _pool->TotalActiveInstances();
	if (_stopProduce && totalActive == 0)
	{
		_isEnabled = false;
		return;
	}
	if (totalActive < _maxParticles && !_stopProduce)
	{
		SpawnParticles(glm::min(_maxParticles - totalActive, maxParticlesPerStep));
	}

	if (_activeParticles.size() > 0)
		for (size_t i = _activeParticles.size() - 1; i > 0; i--)
		{
			Particle* p = _activeParticles[i];
			p->life -= pTime;
			if (p->life > 0.0f)
			{
				p->acceleration += glm::vec3(0, -1, 0)*p->gravity * pTime;
				p->acceleration *= 0.99f;
				p->velocity += p->acceleration;
				p->position += p->velocity*pTime;
				p->color.a -= p->transparencyPerSecond*pTime;
			}
			else
			{
				_pool->Give(p);
				_activeParticles.erase(_activeParticles.begin() + i);
			}
		}
}

void ParticleEmitter::SpawnParticles(int amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		int rand0, rand1, rand2, rand3, rand4, rand5, rand6;
		
		std::uniform_real_distribution<float> unif(0, 1);
		rand0 = unif(e);
		rand1 = unif(e);
		rand2 = unif(e);
		rand3 = unif(e);
		rand4 = unif(e);
		rand5 = unif(e);
		rand6 = unif(e);
		Particle* p = _pool->Take();
		p->life = _original->life;
		p->gravity = _original->gravity;
		p->acceleration = _original->acceleration + glm::vec3(rand0 / 4, rand1, rand1 / 4);
		p->color = _original->color;
		p->position = _original->position + glm::vec3(rand3 / 4, rand4, rand5 / 4);
		p->velocity = _original->velocity + glm::vec3(rand3 / 4, rand6, rand4 / 4);
		p->transparencyPerSecond = _original->transparencyPerSecond;
		p->transparencyStart = _original->transparencyStart;
		_activeParticles.push_back(p);
	}
}

void ParticleEmitter::_initializeShader()
{
	if (_shader == nullptr)
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "colorParticle.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "colorParticle.fs");
		_shader->finalize();
		_shader->use();


		_uMMatrix = _shader->getUniformLocation("modelMatrix");
		_uVMatrix = _shader->getUniformLocation("viewMatrix");
		_uPMatrix = _shader->getUniformLocation("projectionMatrix");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");

		_texture = _shader->getUniformLocation("particleTexture");

		_offset = _shader->getUniformLocation("offset");
		_color = _shader->getUniformLocation("ParticleColor");



	}
}

