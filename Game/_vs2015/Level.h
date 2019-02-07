#ifndef LEVEL_HPP
#define LEVEL_HPP
#include <string>
#include "mge/util/MapGenerator.h"
class Level
{
public:
	Level(std::string map, std::string decoration);
	~Level();
	static Level* instance;
	MapGenerator* GetMap();
	MapGenerator* GetDeco();
private:
	MapGenerator* _map;
	MapGenerator* _decoration;
};

#endif // !LEVEL_HPP
