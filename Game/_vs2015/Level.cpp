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
#include "../_vs2015/Debug.h"
#include "mge/core/Light.hpp"

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

	luaFile = levelLuaFile;

	Reload();
}

void Level::Reload()
{

	std::string mapFile;
	std::string decoFile;

	lua_State* L = luaL_newstate();

	Debug::Log("Reloading Level", ALL);

	luaL_loadfile(L, luaFile.c_str());
	LuaOperations::SaveLuaCall(L, 0, 0, true, "Could not load Level(" + luaFile + ") settings.\n");

	lua_getglobal(L, "heightTexture");
	std::string height;
	if (!LuaOperations::TryGetString(L, &height))
	{
		Debug::Log("Level has no height map", WARNINGS_ERRORS_LOG3);
	}
	else {
		TextureMaterial::_heightMap = Texture::load(config::MGE_TEXTURE_PATH + height, false, true);
	}

	lua_getglobal(L, "map");

	/*
		if (LuaOperations::SaveLuaCall(L, 0, 1, true, "Could not read map settings."))return;*/
	if (!LuaOperations::TryGetString(L, &mapFile))
	{
		Debug::LogError("Error parsing path to map data\n");

		lua_pushstring(L, "Map Parse error");
		lua_error(L);
		_map = nullptr;
		return;
	}
	else
	{

		_map = new MapGenerator(config::MGE_MAP_PATH + mapFile);
	}

	lua_getglobal(L, "deco");

	instance = this;
	/*
		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetString(L, &decoFile))
	{
		Debug::Log("Error parsing path to deco data", WARNINGS_ERRORS_LOG2);

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
		Debug::Log("Error parsing path to background image", WARNINGS_ERRORS_LOG2);
		background = Texture::load(config::MGE_TEXTURE_PATH + "black.png", true);

	}
	else
	{

		background = Texture::load(config::MGE_TEXTURE_PATH + bg, true);
	}

	lua_getglobal(L, "mapGround");
	std::string mbg;
	/*
		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetString(L, &mbg))
	{
		Debug::Log("Error parsing path to Map Ground Texure image", WARNINGS_ERRORS_LOG2);
		mapGround = Texture::load(config::MGE_TEXTURE_PATH + "black.png", true);

	}
	else
	{

		mapGround = Texture::load(config::MGE_TEXTURE_PATH + mbg, true);
	}

	LoadLightParams(L);

	//lua_getglobal(L, "mapGroundNormal");
	//std::string mbgn;
	///*
	//	if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	//if (!LuaOperations::TryGetString(L, &mbgn))
	//{
	//	Debug::Log("Error parsing path to Map Ground Normal Texure image");
	//	mapGroundNormal = Texture::load(config::MGE_TEXTURE_PATH + "black.png");

	//}
	//else
	//{

	//	mapGroundNormal = Texture::load(config::MGE_TEXTURE_PATH + mbgn);
	//}

	lua_getglobal(L, "genOffset");
	double go;
	/*

		if (LuaOperations::SaveLuaCall(L, 0, 1, false, "Could not read deco settings."))return;*/
	if (!LuaOperations::TryGetDouble(L, &go))
	{
		Debug::Log("Error parsing Generation offset from map file. Default = 75", WARNINGS_ERRORS_LOG2);


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
		Debug::Log("Error parsing xCurvature from map file. Default = 50", WARNINGS_ERRORS_LOG2);
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
		Debug::Log("Error parsing xCurvatureSmoothness from map file. Default = 2", WARNINGS_ERRORS_LOG2);

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
		Debug::Log("Error parsing HeightMapTiling from map file. Default = 1", WARNINGS_ERRORS_LOG2);

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
		Debug::Log("Error parsing heightMapSpeed from map file. Default = 0", WARNINGS_ERRORS_LOG2);

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
		Debug::Log("Error parsing heightMapMaxHeight from map file. Default = 10", WARNINGS_ERRORS_LOG2);

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
		Debug::Log("Error parsing Height Sampling Width from map file. Default = 8", WARNINGS_ERRORS_LOG2);


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
		Debug::Log("Error parsing xMoveTiling from map file. Default = 100", WARNINGS_ERRORS_LOG2);
		TextureMaterial::xMoveTiling = 100;
	}
	else
	{
		TextureMaterial::xMoveTiling = (float)xMT;
	}

	lua_getglobal(L, "fogColor");
	glm::vec3 fogColor = glm::vec3(0.5);
	if (!LuaOperations::TryGetFloatFromTable(L, "Red", &fogColor.r))
	{

		Debug::Log("Fog Color could not be found in file. Default (0.5, 0.5, 0.5)(Grey)", WARNINGS_ERRORS_LOG2);
	}
	else
	{
		lua_getglobal(L, "fogColor");
		if (!LuaOperations::TryGetFloatFromTable(L, "Green", &fogColor.g))
		{
			Debug::Log("Fog Color could not be found in file. Default (0.5, 0.5, 0.5)(Grey)", WARNINGS_ERRORS_LOG2);
		}
		else
		{
			lua_getglobal(L, "fogColor");
			if (!LuaOperations::TryGetFloatFromTable(L, "Blue", &fogColor.b))
			{
				Debug::Log("Fog Color could not be found in file. Default (0.5, 0.5, 0.5)(Grey)", WARNINGS_ERRORS_LOG2);
			}
		}
	}

	TextureMaterial::fogColor = fogColor;


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
Texture* Level::GetMapGroundNormal()
{
	return mapGroundNormal;
}

void Level::LoadLightParams(lua_State* L)
{
	lua_getglobal(L, "lightParameter");
	std::string lightParameter = "";
	LightParams p;
	if (!LuaOperations::TryGetString(L, &lightParameter))
	{
		Debug::Log("Could not read lightParameter field", DebugLevel::WARNINGS_ERRORS_LOG2);
		p = LightParams();
	}
	else {
		p = LightParams(config::MGE_LIGHT_PATH + lightParameter);
	}
	Light::mapLight->SetParams(p);
}

void Level::LoadLightParams()
{
	lua_State* L = luaL_newstate();

	luaL_loadfile(L, luaFile.c_str());
	LuaOperations::SaveLuaCall(L, 0, 0, true, "Could not load Level(" + luaFile + ") settings.\n");
	LoadLightParams(L);
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
