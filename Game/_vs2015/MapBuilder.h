#ifndef MAPBUILDER_HPP
#define MAPBUILDER_HPP
#include <vector>
#include "mge/util/Lane.h"
#include "mge/core/GameObject.hpp"

class MapBuilder
{
public:
	MapBuilder(float generationOffset, float segmentStep);
	void Update(float ptime);
	std::vector<std::pair<int, GameObject*>> PrepareMap(std::vector<Lane*> lanes, size_t length);

private:
	GameObject* _container;
	std::vector<std::pair<int, GameObject*>> map;
	float genOffset;
	float totalTime;
	int segmentCount;
	int lanes;
	float segStep;
};

#endif // !MAPBUILDER_HPP
