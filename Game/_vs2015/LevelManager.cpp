#include "LevelManager.h"
#include "Level.h"
#include <string>
#include <vector>
#include "LuaOperations.h"
#include "mge/config.hpp"
#include "GameStateManager.h"

LevelManager* LevelManager::instance = nullptr;

LevelManager::LevelManager(std::string luaMapList)
{
	
	_currentLevel = nullptr;
	instance = this;
	lua_State* L = luaL_newstate();

	luaL_loadfile(L, luaMapList.c_str());
	LuaOperations::SaveLuaCall(L, 0, 0, true, "Could not load map list.");

	lua_getglobal(L, "levels");

	if (!LuaOperations::TableToVector(L, &_maps))
	{
		std::cout << "could not read levels from map list\n";
		return;
	}

	lua_close(L);
}

void LevelManager::ChangeLevel(int index)
{
	if (_maps.size() == 0)return;
	if (_currentLevel != nullptr)
	{
		_currentLevel->Unload();
		delete _currentLevel;
		_currentLevel = nullptr;

	}
	_curLevel = index % _maps.size();

	_currentLevel = new Level(config::MGE_MAP_PATH+_maps[_curLevel]);

	if (_curLevel < (int)_backgroundTextures.size()-1)
	{
		// cahnge background texture
	}

	if (_curLevel < (int)_groundTextures.size()-1)
	{
		// cahnge ground texture
	}

}

void LevelManager::NextLevel()
{
	if (_curLevel == (int)_maps.size() - 1)
	{
		//display you win screen
	}
	ChangeLevel(_curLevel + 1);
}

int LevelManager::GetCurrent()
{
	return _curLevel;
}

void LevelManager::AddGroundTexture(std::string pFileLocation)
{
	_groundTextures.push_back(pFileLocation);
}

void LevelManager::AddBackgroundTexture(std::string pFileLocation)
{
	_backgroundTextures.push_back(pFileLocation);
}