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
	Texture* GetBackground();
	Texture* GetMapGround();
	Texture* GetMapGroundNormal();
	void Unload();
private:
	MapGenerator* _map;
	MapGenerator* _decoration;
	Texture* background;
	Texture* mapGround;
	Texture* mapGroundNormal;
};

#endif // !LEVEL_HPP
