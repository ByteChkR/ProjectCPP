#ifndef LEVEL_HPP
#define LEVEL_HPP
#include <string>
#include "mge/core/Texture.hpp"
#include "mge/util/MapGenerator.h"
#include "mge/materials/TextureMaterial.hpp"
class Level
{
public:
	Level(bool debug, std::string mapFile);
	Level(std::string levelLuaFile);
	~Level();
	static Level* instance;
	MapGenerator* GetMap();
	MapGenerator* GetDeco();
	void Unload();
private:
	MapGenerator* _map;
	MapGenerator* _decoration;
};

#endif // !LEVEL_HPP
