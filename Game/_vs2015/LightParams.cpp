#include "LightParams.hpp"
#include <string>
#include "LuaOperations.h"
#include "lua.hpp"
#include "Debug.h"
LightParams::LightParams(int type, float intensity, glm::vec2 attenuation,
	glm::vec3 color, glm::vec3 ambientColor)
{

	this->type = type;
	this->intensity = intensity;
	this->attenuation = attenuation;
	this->color = color;
	this->ambientColor = ambientColor;
}

LightParams::LightParams(std::string file) : LightParams()
{

	lua_State* L = luaL_newstate();

	int test = luaL_loadfile(L, file.c_str());
	LuaOperations::SaveLuaCall(L, 0, 0, true, "Could not load light params. " + file);


	lua_getglobal(L, "intensity");
	if (!LuaOperations::TryGetFloat(L, &intensity))
	{
		Debug::Log("Could not read light intensity. Default = 1", WARNINGS_ERRORS_LOG2);
		intensity = 1;
	}

	lua_getglobal(L, "attenuationLinear");
	if (!LuaOperations::TryGetFloat(L, &attenuation.x))
	{
		Debug::Log("Could not read linear attenuation. Default = 0.01", WARNINGS_ERRORS_LOG2);
		attenuation.x = 0.01f;
		lua_getglobal(L, "attenuationSquared");
		if (!LuaOperations::TryGetFloat(L, &attenuation.y))
		{
			Debug::Log("Could not read linear attenuation. Default = 0.02", WARNINGS_ERRORS_LOG2);
			attenuation.x = 0.01f;
		}
	}
	lua_getglobal(L, "colorRed");
	if (!LuaOperations::TryGetFloat(L, &color.r))
	{
		Debug::Log("Could not read light color component red. Default = 1", WARNINGS_ERRORS_LOG2);
	}
	lua_getglobal(L, "colorGreen");
	if (!LuaOperations::TryGetFloat(L, &color.g))
	{
		Debug::Log("Could not read light color component green. Default = 1", WARNINGS_ERRORS_LOG2);
	}
	lua_getglobal(L, "colorBlue");
	if (!LuaOperations::TryGetFloat(L, &color.b))
	{
		Debug::Log("Could not read light color component blue. Default = 1", WARNINGS_ERRORS_LOG2);
	}

	lua_getglobal(L, "ambientColorRed");
	if (!LuaOperations::TryGetFloat(L, &ambientColor.r))
	{
		Debug::Log("Could not read light ambient color component red. Default = 0.2", WARNINGS_ERRORS_LOG2);
	}

	lua_getglobal(L, "ambientColorGreen");
	if (!LuaOperations::TryGetFloat(L, &ambientColor.g))
	{
		Debug::Log("Could not read light ambient color component green. Default = 0.2", WARNINGS_ERRORS_LOG2);
	}

	lua_getglobal(L, "ambientColorBlue");
	if (!LuaOperations::TryGetFloat(L, &ambientColor.b))
	{
		Debug::Log("Could not read light ambient color component blue. Default = 0.2", WARNINGS_ERRORS_LOG2);
	}

	lua_close(L);

}