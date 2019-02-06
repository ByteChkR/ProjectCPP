#ifndef OBJECTPOOL_HPP
#define OBJECTPOOL_HPP
#include <vector>

template <typename T>
class ObjectPool
{
public:
	ObjectPool(T original);
	T Take();
	void Give(T val);
private:
	std::vector<T> _buffer;
	std::vector<T> _activeBuffer;
	T _original;
};

#endif // !OBJECTPOOL_HPP