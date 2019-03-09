#include "EngineSettings.h"
#include "LuaOperations.h"
#include <string>
#include "lua.hpp"
#include <iostream>
#include "../_vs2015/Debug.h"
#include "FileLoader.h"

EngineSettings* EngineSettings::settings = nullptr;

EngineSettings::EngineSettings(std::string file)
{
	settings = this;
	lua_State* L = luaL_newstate();

	luaL_loadfile(L, file.c_str());
	LuaOperations::SaveLuaCall(L, 0, 0, true, "Could not load engine settings.");

	LuaOperations::TryGetIntFromGlobal(L, "width", &_width, true, "Could not read Width");
	LuaOperations::TryGetIntFromGlobal(L, "height", &_height, true, "Could not read Height");
	if (!LuaOperations::TryGetIntFromGlobal(L, "FPSTarget", &_fpsTarget, false))Debug::Log("Could not read FPSTarget", WARNINGS_ERRORS_LOG2);
	if (!LuaOperations::TryGetStringFromGlobal(L, "WindowName", &_windowName, false))Debug::Log("Could not read Window Name", WARNINGS_ERRORS_LOG2);
	
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

int EngineSettings::GetFPSTarget()
{
	return _fpsTarget;
}