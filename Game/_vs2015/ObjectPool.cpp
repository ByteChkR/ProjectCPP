#include "ObjectPool.hpp"
#include "mge/core/GameObject.hpp"
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

void ObjectPool<GameObject*>::Give(GameObject*  val)
{
	
	for (size_t i = 0; i < _activeBuffer.size(); i++)
	{
		if(_activeBuffer[i] == val)
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
	
	GameObject* r = _buffer[bufferSize-1];
	_buffer.pop_back();
	_activeBuffer.push_back(r);
	return r;
}
