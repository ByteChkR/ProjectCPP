#ifndef LEVEL_HPP
#define LEVEL_HPP
#include <string>
#include "mge/core/Texture.hpp"
#include "mge/util/MapGenerator.h"
class Level
{
public:
	Level(std::string levelLuaFile);
	~Level();
	static Level* instance;
	Texture* heightMap;
	MapGenerator* GetMap();
	MapGenerator* GetDeco();
	void Unload();
private:
	MapGenerator* _map;
	MapGenerator* _decoration;
};

#endif // !LEVEL_HPP
