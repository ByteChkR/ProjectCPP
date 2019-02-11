#include "LevelManager.h"
#include "Level.h"
#include <string>
#include <vector>
#include "LuaOperations.h"
#include "mge/config.hpp"

LevelManager* LevelManager::instance = nullptr;

LevelManager::LevelManager(std::string luaMapList)
{
	currentLevel = nullptr;
	instance = this;
	lua_State* L = luaL_newstate();

	luaL_loadfile(L, luaMapList.c_str());
	LuaOperations::SaveLuaCall(L, 0, 0, true, "Could not load map list.");

	lua_getglobal(L, "levels");

	if (!LuaOperations::TableToVector(L, &maps))
	{
		std::cout << "could not read levels from map list\n";
		return;
	}

	lua_close(L);
}

void LevelManager::ChangeLevel(int index)
{
	if (maps.size() == 0)return;
	if (currentLevel != nullptr)
	{
		currentLevel->Unload();
		delete currentLevel;
		currentLevel = nullptr;

	}

	currentLevel = new Level(config::MGE_MAP_PATH+maps[index%maps.size()]);

}