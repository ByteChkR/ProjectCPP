#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H
#include <vector>
#include <SFML\Graphics.hpp>
#include "mge\util\Lane.h"

class MapGenerator
{
public:

	static MapGenerator * instance;

	MapGenerator();
	~MapGenerator();
	Lane* GetLaneAt(int pIndex);

private:
	std::vector<Lane *> _lanes;
};

#endif

