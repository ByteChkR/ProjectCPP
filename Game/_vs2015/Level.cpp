#include "Level.h"
#include <string>
#include "MapBuilder.h"
#include "mge/util/MapGenerator.h"
#include "lua.hpp"
#include "LuaOperations.h"
#include "mge/config.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/util/DataManager.h"
#include "../_vs2015/TextureMovingMaterial.h"
#include "mge\materials\AnimationMaterial.hpp"

Level* Level::instance = nullptr;


Level::Level(bool debug, std::string mapFile)
{
	_map = new MapGenerator(mapFile);
	_decoration = nullptr;
	instance = this;
	if (MapBuilder::instance != nullptr)MapBuilder::instance->Reload();
}

Level::Level(std::string levelLuaFile)
{
	if(MapBuilder::instance != nullptr) MapBuilder::instance->Unload(); //Give back all "prefabs" to the object pools


	std::string mapFile;
	std::string decoFile;

	lua_State* L = luaL_newstate();

	luaL_loadfile(L, levelLuaFile.c_str());
	LuaOperations::SaveLuaCall(L, 0, 0, true, "Could not load Level("+levelLuaFile+") settings.\n");

	lua_getglobal(L, "heightTexture");
	std::string height;
	if (!LuaOperations::TryGetString(L, &height))
	{
		std::cout << "Level has no height map\n";
	}
	else {
		TextureMaterial::_heightMap = Texture::load(config::MGE_TEXTURE_PATH + height, true);
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
	}
	else
	{

		_decoration = new MapGenerator(decoFile, false);
	}


	lua_getglobal(L, "ground");
	std::string bg;
	/*
		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetString(L, &bg))
	{
		std::cout << "Error parsing path to background image\n";
		background = Texture::load(config::MGE_TEXTURE_PATH + "black.png");

	}
	else
	{

		background = Texture::load(config::MGE_TEXTURE_PATH + bg);
	}

	lua_getglobal(L, "mapGround");
	std::string mbg;
	/*
		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetString(L, &mbg))
	{
		std::cout << "Error parsing path to Map Ground Texure image\n";
		mapGround = Texture::load(config::MGE_TEXTURE_PATH + "black.png");

	}
	else
	{

		mapGround = Texture::load(config::MGE_TEXTURE_PATH + mbg);
	}

	lua_getglobal(L, "genOffset");
	double go;
	/*
	
		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetDouble(L, &go))
	{
		std::cout << "Error parsing Generation offset from map file. Default = 75\n";
		

		TextureMaterial::genOffset = 75;
		MapBuilder::instance->genOffset = 75;
	}
	else
	{
		TextureMaterial::genOffset = (float)go;
		MapBuilder::instance->genOffset = (float)go;
	}

	lua_getglobal(L, "xCurvature");
	double xCurv;
	/*

		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetDouble(L, &xCurv))
	{
		std::cout << "Error parsing xCurvature from map file. Default = 50\n";
		TextureMaterial::maxXOff = 50;

	}
	else
	{
		TextureMaterial::maxXOff = (float)xCurv;
		
	}

	lua_getglobal(L, "xCurvatureSmoothness");
	double xCurvSmooth;
	/*

		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetDouble(L, &xCurvSmooth))
	{
		std::cout << "Error parsing xCurvatureSmoothness from map file. Default = 2\n";

		TextureMaterial::xOffsetSmootness = 2;
	}
	else
	{

		TextureMaterial::xOffsetSmootness = (float)xCurvSmooth;
	}

	lua_getglobal(L, "heightMapTiling");
	double hmTiling;
	/*

		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetDouble(L, &hmTiling))
	{
		std::cout << "Error parsing HeightMapTiling from map file. Default = 1\n";

		TextureMaterial::heightmapTiling = 1;

	}
	else
	{
		TextureMaterial::heightmapTiling = (float)hmTiling;
	}

	lua_getglobal(L, "heightMapSpeed");
	double hmSpeed;
	/*

		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetDouble(L, &hmSpeed))
	{
		std::cout << "Error parsing heightMapSpeed from map file. Default = 0\n";

		TextureMaterial::heightmapSpeed = 0;

	}
	else
	{
		TextureMaterial::heightmapSpeed = (float)hmSpeed;
	}

	lua_getglobal(L, "heightMapMaxHeight");
	double hmHeight;
	/*

		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetDouble(L, &hmHeight))
	{
		std::cout << "Error parsing heightMapMaxHeight from map file. Default = 10\n";

		TextureMaterial::maxHeight = 10;
	}
	else
	{
		TextureMaterial::maxHeight = (float)hmHeight;
	}

	lua_getglobal(L, "heightMapSamplingWidth");
	double hmSW;
	/*

		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetDouble(L, &hmSW))
	{
		std::cout << "Error parsing Height Sampling Width from map file. Default = 8\n";
		

		TextureMaterial::width = 8;
	}
	else
	{
		TextureMaterial::width = (float)hmSW;
	}

	lua_getglobal(L, "xMoveTiling");
	double xMT;
	/*

		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetDouble(L, &xMT))
	{
		std::cout << "Error parsing xMoveTiling from map file. Default = 100\n";
		TextureMaterial::xMoveTiling = 100;
	}
	else
	{
		TextureMaterial::xMoveTiling = (float)xMT;
	}

	//Insert logic for data manager here.
	//I Am Supplying with Textures, you have gameobjects.
	if (DataManager::instance->GetBackground()->getMaterial() != nullptr && DataManager::instance->GetGround()->getMaterial() != nullptr)
	{
		dynamic_cast<AnimationMaterial*>(DataManager::instance->GetBackground()->getMaterial())->setDiffuseTexture(background);
		dynamic_cast<TextureMovingMaterial*>(DataManager::instance->GetGround()->getMaterial())->setDiffuseTexture(mapGround);
	}
	
	

	MapBuilder::instance->Reload();
}

Texture* Level::GetBackground()
{
	return background;
}
Texture* Level::GetMapGround()
{
	return mapGround;
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