#include "ObjectPool.hpp"
#include "mge/core/GameObject.hpp"
#include "Particle.h"

#pragma region GameObject
ObjectPool<GameObject*>::ObjectPool(GameObject*  original)
{
	_original = original;
	_buffer = std::vector<GameObject*>();
	_activeBuffer = std::vector<GameObject*>();
}

ObjectPool<GameObject*>::~ObjectPool()
{
	_activeBuffer.clear();
	_buffer.clear();
	delete _original;
	_original = nullptr;
}

int ObjectPool<GameObject*>::TotalInstances()
{
	return _buffer.size() + _activeBuffer.size();
}
int ObjectPool<GameObject*>::TotalActiveInstances()
{
	return _activeBuffer.size();
}

void ObjectPool<GameObject*>::Give(GameObject*  val)
{

	for (size_t i = 0; i < _activeBuffer.size(); i++)
	{
		if (_activeBuffer[i] == val)
		{
			_activeBuffer.erase(_activeBuffer.begin() + i);
			_buffer.push_back(val);
		}
	}
}

GameObject* ObjectPool<GameObject*>::Take()
{
	int bufferSize = _buffer.size();
	if (bufferSize == 0)
	{
		GameObject* _ret = _original->Clone();
		_activeBuffer.push_back(_ret);
		return _ret;
	}

	GameObject* r = _buffer[bufferSize - 1];
	_buffer.pop_back();
	_activeBuffer.push_back(r);
	return r;
}

#pragma endregion

#pragma region Particle
ObjectPool<Particle*>::ObjectPool(Particle*  original)
{
	_original = original;
	_buffer = std::vector<Particle*>();
	_activeBuffer = std::vector<Particle*>();
}

ObjectPool<Particle*>::~ObjectPool()
{
	_activeBuffer.clear();
	_buffer.clear();
	
	delete _original;
	_original = nullptr;
}

int ObjectPool<Particle*>::TotalInstances()
{
	return _buffer.size() + _activeBuffer.size();
}
int ObjectPool<Particle*>::TotalActiveInstances()
{
	return _activeBuffer.size();
}

void ObjectPool<Particle*>::Give(Particle*  val)
{

	for (size_t i = 0; i < _activeBuffer.size(); i++)
	{
		if (_activeBuffer[i] == val)
		{
			_activeBuffer.erase(_activeBuffer.begin() + i);
			_buffer.push_back(val);
		}
	}
}

Particle* ObjectPool<Particle*>::Take()
{
	int bufferSize = _buffer.size();
	if (bufferSize == 0)
	{
		Particle* _ret = _original->Clone();
		_activeBuffer.push_back(_ret);
		return _ret;
	}

	Particle* r = _buffer[bufferSize - 1];
	_buffer.pop_back();
	_activeBuffer.push_back(r);
	return r;
}

#pragma endregion


