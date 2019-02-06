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
	Lane* GetLaneAt(int pIndex);

private:
	float _laneSpace = 2;
	std::string _filePath = "mge/maps/";
	std::vector<Lane *> _lanes;
};

#endif

