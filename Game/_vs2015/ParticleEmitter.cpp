#include "ParticleEmitter.h"
#include "Particle.h"
#include "glm.hpp"
#include "mge/core/Mesh.hpp"
#include <vector>
#include "mge/config.hpp"
#include "ParticleSystem.h"
#include <random>
#include "mge/core/Texture.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include <chrono>
#include "mge/core/AbstractGame.hpp"
#include <iostream>
#include "PlayerController.hpp"

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
GLint ParticleEmitter::_heightTexID = 0;
GLint ParticleEmitter::_maxHeight = 0;
GLint ParticleEmitter::_time = 0;
GLint ParticleEmitter::_genOffset = 0;
GLint ParticleEmitter::_hwm = 0;
GLint ParticleEmitter::_heightMapTiling = 0;
GLint ParticleEmitter::_heightMapSpeed = 0;
GLint ParticleEmitter::_xMoveTiling = 0;
GLint ParticleEmitter::_xOffsetSmoothness = 0;
GLint ParticleEmitter::_maxXOffset = 0;


std::default_random_engine ParticleEmitter::e;

ParticleEmitter::ParticleEmitter(Particle* original, Texture* particleTexture, int maxParticles, float maxParticlesPerStep, bool useTimeScale)
{
	this->useTimeScale = useTimeScale;
	this->maxParticlesPerStep = maxParticlesPerStep;
	_particleTexture = particleTexture;
	e = std::default_random_engine(seed);
	ParticleSystem::instance->RegisterParticleEmitter(this);
	_original = original;
	_pool = new ObjectPool<Particle*>(_original);
	_maxParticles = maxParticles;
	_activeParticles = std::vector<Particle*>();
	_isEnabled = false;
	_stopProduce = false;
	curParticleAmount = 0;

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

void ParticleEmitter::StartBurst(int particles)
{
	if (_isEnabled) return;
	_isEnabled = true;
	SpawnParticles(particles);
	_stopProduce = true;
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

void ParticleEmitter::SetOpacityMode(bool enabled)
{
	_enableAlpha = enabled;
}

void ParticleEmitter::render(int pass, World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pPerspectiveMatrix)
{
	if (pass != 1)return;
	_shader->use();
	if (_enableAlpha)glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);




	glUniformMatrix4fv(_uPMatrix, 1, GL_FALSE, glm::value_ptr(pPerspectiveMatrix));
	glUniformMatrix4fv(_uVMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_uMMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	if (_particleTexture != nullptr || _texture == -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _particleTexture->getId());
		glUniform1i(_texture, 0);
	}
	if (TextureMaterial::_heightMap != nullptr)
	{
		//setup texture slot 0
		glActiveTexture(GL_TEXTURE1);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, TextureMaterial::_heightMap->getId());
		//tell the shader the texture slot for the diffuse texture is slot 0
		glUniform1i(_heightTexID, 1);

		glUniform1f(_maxHeight, TextureMaterial::maxHeight);

	}
	glUniform1f(_xMoveTiling, TextureMaterial::xMoveTiling);
	glUniform1f(_xOffsetSmoothness, TextureMaterial::xOffsetSmootness);
	glUniform1f(_maxXOffset, TextureMaterial::maxXOff);
	glUniform1f(_heightMapSpeed, TextureMaterial::heightmapSpeed);
	glUniform1f(_heightMapTiling, TextureMaterial::heightmapTiling);
	glUniform1f(_time, AbstractGame::instance->GetTimeSinceStartup());
	glUniform1f(_genOffset, TextureMaterial::genOffset);
	glUniform1f(_hwm, TextureMaterial::width);

	for (size_t i = 0; i < _activeParticles.size(); i++)
	{
		if (_activeParticles[i]->life > 0.0f)
		{
			//Set Shader Attribs(pos/color)
			glUniform4f(_color, _activeParticles[i]->color.x, _activeParticles[i]->color.y, _activeParticles[i]->color.z, _activeParticles[i]->color.w);
			glUniform3f(_offset, _activeParticles[i]->position.x, _activeParticles[i]->position.y, _activeParticles[i]->position.z);
			//Render to opengl via mesh.streamtoopengl

			pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV, -1, -1);
		}
	}


	glDepthMask(GL_TRUE);
	if (_enableAlpha)glDisable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void ParticleEmitter::UpdateParticles(float pTime)
{
	
	float realTime = useTimeScale ? pTime : pTime * AbstractGame::instance->GetTimeScale();

	int totalActive = _activeParticles.size();
	if (_stopProduce && totalActive == 0)
	{
		_isEnabled = false;
		return;
	}
	if ((int)_activeParticles.size() < _maxParticles && !_stopProduce)
	{
		curParticleAmount += maxParticlesPerStep;

		SpawnParticles(glm::min(_maxParticles - totalActive, (int)curParticleAmount));
		curParticleAmount = glm::mod(curParticleAmount, 1.0f);
		//std::cout << "Adding particles: " << std::to_string(_maxParticles - totalActive) << "\n";
	}
 	if (_activeParticles.size() > 0)
		for (size_t i = _activeParticles.size(); i > 0; --i)
		{
			Particle* p = _activeParticles[i-1];
			p->life -= realTime;
			if (p->life > 0.0f)
			{
				p->acceleration += glm::vec3(0, -1, 0)*p->gravity * realTime;
				p->acceleration *= 0.99f;
				p->velocity += p->acceleration;
				p->position += p->velocity*realTime;
				//p->color.a -= p->transparencyPerSecond*pTime;
			}
			else
			{
				_pool->Give(p);
				_activeParticles.erase(_activeParticles.begin() + (i-1));
			}
		}
}

void ParticleEmitter::SpawnParticles(size_t amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		float rand0, rand1, rand2, rand3, rand4, rand5, rand6;

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
		p->acceleration = _original->acceleration + glm::vec3((2 * rand0 - 1) / 2, 0, (2 * rand1 - 1) / 2);
		p->color = _original->color;
		p->position = _original->position;
		p->velocity = _original->velocity;
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

		_xOffsetSmoothness = _shader->getUniformLocation("xOffsetSmoothness");
		_xMoveTiling = _shader->getUniformLocation("xMoveTiling");
		_maxXOffset = _shader->getUniformLocation("maxXOffset");

		_texture = _shader->getUniformLocation("particleTexture");

		_offset = _shader->getUniformLocation("offset");
		_color = _shader->getUniformLocation("ParticleColor");

		_heightTexID = _shader->getUniformLocation("heightMap");
		_maxHeight = _shader->getUniformLocation("maxHeight");
		_genOffset = _shader->getUniformLocation("genOffset");
		_hwm = _shader->getUniformLocation("hwm");
		_heightMapSpeed = _shader->getUniformLocation("heightMapSpeed");
		_time = _shader->getUniformLocation("time");
		_heightMapTiling = _shader->getUniformLocation("heightMapTiling");

	}
}

