#include "MapGenerator.h"

MapGenerator * MapGenerator::instance;

MapGenerator::MapGenerator()
{
	instance = this;

	Lane * lane1 = new Lane(glm::vec3(-2, 0, 0), -1, 1, 0, 0);
	Lane * lane2 = new Lane(glm::vec3(0, 0, 0), 0, 2, 0, 0);
	Lane * lane3 = new Lane(glm::vec3(0, 0, 2), 1, -1, 0, 0);
	_lanes.push_back(lane1);
	_lanes.push_back(lane2);
	_lanes.push_back(lane3);
}


MapGenerator::~MapGenerator()
{
}

Lane* MapGenerator::GetLaneAt(int pIndex)
{
	if (pIndex > _lanes.size() - 1)
	{
		printf("Lane is out of the range");
	}

	return _lanes[pIndex];
}
