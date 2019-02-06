#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H
#include <vector>
#include <SFML\Graphics.hpp>
#include "mge\util\Lane.h"

class MapGenerator
{
public:

	static MapGenerator * instance;

	MapGenerator(std::string pName);
	~MapGenerator();
	std::vector<Lane*> GetAllLanes();
	size_t GetNumberOfLanes();
	Lane* GetLaneAt(size_t pIndex);


private:
	float _laneSpace = 2;
	std::string _filePath = "mge/maps/";
	std::vector<Lane *> _lanes;
};

#endif

