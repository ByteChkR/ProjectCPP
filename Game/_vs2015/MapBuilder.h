#ifndef MAPBUILDER_HPP
#define MAPBUILDER_HPP
#include <vector>
#include "mge/util/Lane.h"

class MapBuilder
{
public:
	MapBuilder(float generationOffset, float segmentStep);
	void Update(float ptime);
	void PrepareMap(std::vector<Lane*> lanes, int length);

private:
	
	float genOffset;
	float segStep;
};

#endif // !MAPBUILDER_HPP
