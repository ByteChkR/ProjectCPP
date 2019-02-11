#include "EngineSettings.h"
#include "LuaOperations.h"
#include <string>
#include "lua.hpp"
#include <iostream>
EngineSettings::EngineSettings(const char* file)
{
	lua_State* L = luaL_newstate();

	luaL_loadfile(L, file);
	LuaOperations::SaveLuaCall(L, 0, 0, true, "Could not load engine settings.");

	int test = lua_gettop(L);
	lua_getglobal(L, "GetWindow");
	if (LuaOperations::SaveLuaCall(L, 0, 1, true, "Could not read engine settings."))return;
	if (!LuaOperations::TryGetIntFromTable(L, "width", &_width))
	{
		_width = 900;
		std::cout << "Engine Settings File " << file << " has no field for width. Default = 900";
		//Error
	}

	lua_getglobal(L, "GetWindow");
	if (LuaOperations::SaveLuaCall(L, 0, 1, true, "Could not read engine settings."))return;

	if (!LuaOperations::TryGetIntFromTable(L, "height", &_height))
	{
		_height = 600;
		std::cout << "Engine Settings File " << file << " has no field for height. Default = 600";
		//Error
	}

	lua_getglobal(L, "GetWindow");
	if (LuaOperations::SaveLuaCall(L, 0, 1, true, "Could not read engine settings."))return;

	if (!LuaOperations::TryGetStringFromTable(L, "windowName", &_windowName))
	{
		_windowName = "NO NAME";
		std::cout << "Engine Settings File " << file << " has no field for windowName. Default = NO NAME";
		//Error
	}
	lua_close(L);
}

int EngineSettings::GetHeight()
{
	return _height;
}

int EngineSettings::GetWidth()
{
	return _width;
}

std::string EngineSettings::GetWindowName()
{
	return _windowName;
}