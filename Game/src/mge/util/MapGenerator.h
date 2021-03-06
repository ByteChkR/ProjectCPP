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

	MapGenerator(std::string pName, bool isInstance = true);
	~MapGenerator();
	std::vector<Lane*> GetAllLanes();
	size_t GetNumberOfLanes();
	Lane* GetLaneAt(size_t pIndex);
	std::vector <int> GetBiomes();
	int GetBiomeAt(int pNumber);
	size_t GetPartCount();
	int NextInt(std::string file, int index, int* charsRead);

private:

	static const int ZERO_ID = '0';
	static const int NINE_ID = '9';

	unsigned seed = unsigned(std::chrono::system_clock::now().time_since_epoch().count());
	static std::default_random_engine e;
	std::string _mapsLocation = "mge/maps/";
	float _laneSpace = 2;
	std::vector<Lane *> _lanes;
	std::vector <int> _biomes;
};

#endif

