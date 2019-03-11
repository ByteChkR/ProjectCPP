#ifndef LEVEL_HPP
#define LEVEL_HPP
#include <string>
#include "mge/core/Texture.hpp"
#include "mge/util/MapGenerator.h"
#include "mge/materials/TextureMaterial.hpp"
#include "lua.hpp"
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
	void LoadLightParams(lua_State* L);
	void LoadLightParams();
	void Unload();
	void Reload();
private:
	MapGenerator* _map;
	MapGenerator* _decoration;
	Texture* background;
	Texture* mapGround;
	Texture* mapGroundNormal;
	std::string luaFile;

};

#endif // !LEVEL_HPP
