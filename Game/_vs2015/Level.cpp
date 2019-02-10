#include "Level.h"
#include <string>
#include "MapBuilder.h"
#include "mge/util/MapGenerator.h"
#include "lua.hpp"
#include "LuaOperations.h"
#include "mge/config.hpp"

Level* Level::instance = nullptr;


Level::Level(std::string levelLuaFile)
{
	if(MapBuilder::instance != nullptr) MapBuilder::instance->Unload(); //Give back all "prefabs" to the object pools


	std::string mapFile;
	std::string decoFile;

	lua_State* L = luaL_newstate();

	luaL_loadfile(L, levelLuaFile.c_str());
	LuaOperations::SaveLuaCall(L, 0, 0, true, "Could not load Level("+levelLuaFile+") settings.");

	lua_getglobal(L, "heightTexture");
	std::string height;
	if (!LuaOperations::TryGetString(L, &height))
	{
		std::cout << "Level has no height map";
	}
	else {
		heightMap = Texture::load(config::MGE_TEXTURE_PATH + height, true);
	}

	lua_getglobal(L, "map");

/*
	if (LuaOperations::SaveLuaCall(L, 0, 1, true, "Could not read map settings."))return;*/
	if (!LuaOperations::TryGetString(L, &mapFile))
	{
		std::cout << "Error parsing path to map data\n";

		lua_pushstring(L, "Map Parse error");
		lua_error(L);
		_map = nullptr;
		return;
	}
	else
	{

		_map = new MapGenerator(mapFile);
	}
	
	lua_getglobal(L, "deco");

	instance = this;
/*
	if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetString(L, &decoFile))
	{
		std::cout << "Error parsing path to deco data\n";

		_decoration = nullptr;
		return;
	}
	else
	{

		_decoration = new MapGenerator(decoFile, false);
	}


	


	MapBuilder::instance->Reload();
}
Level::~Level()
{
	_map = nullptr;
	_decoration = nullptr;
}
MapGenerator* Level::GetDeco()
{
	return _decoration;
}

MapGenerator* Level::GetMap()
{
	return _map;
}

void Level::Unload()
{
	if(MapBuilder::instance != nullptr)MapBuilder::instance->Unload(); //Gives back all props & reloads them from the level singleton
}