#include "LevelManager.h"
#include "Level.h"
#include <string>
#include <vector>
#include "LuaOperations.h"
#include "mge/config.hpp"
#include "PlayerController.hpp"
#include "GameStateManager.h"
#include "../_vs2015/Debug.h"
LevelManager* LevelManager::instance = nullptr;

LevelManager::LevelManager(std::string luaMapList, bool storyMode)
{
	_storyMode = storyMode;
	_currentLevel = nullptr;
	instance = this;
	lua_State* L = luaL_newstate();

	luaL_loadfile(L, luaMapList.c_str());
	LuaOperations::SaveLuaCall(L, 0, 0, true, "Could not load map list.");

	lua_getglobal(L, "levels");

	if (!LuaOperations::TableToVector(L, &_maps))
	{
		Debug::LogError("could not read levels from map list");
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

	PlayerController::instance->SetCurrentLane(_currentLevel->GetMap()->GetNumberOfLanes() / 2);


}

void LevelManager::NextLevel()
{
	if (_curLevel == (int)_maps.size() - 1)
	{
		//display you win screen
	}
	ChangeLevel(_curLevel + 1);
}

void LevelManager::ReloadLevel()
{
	ChangeLevel(_curLevel);
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

