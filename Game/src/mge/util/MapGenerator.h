#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H
#include <vector>
#include <SFML\Graphics.hpp>
#include "mge\util\Lane.h"
#include <algorithm>    // std::shuffle
#include <vector>       // std::vector
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

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
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e;
	float _laneSpace = 2;
	std::string _filePath = "mge/maps/";
	std::vector<Lane *> _lanes;
};

#endif

