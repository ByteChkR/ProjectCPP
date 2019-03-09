#include "LuaOperations.h"
#include <type_traits>
#include <string>
#include <iostream>
#include "lua.hpp"
LuaOperations::LuaOperations() {}

int LuaOperations::TryGetDouble(lua_State* L, double* value)
{
	if (lua_gettop(L) < 1 || !lua_isnumber(L, -1) || lua_isnil(L, -1))
	{
		*value = 0;
		lua_pop(L, 1);
		return 0; //Stack contains no number
	}
	*value = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return 1;
}

int LuaOperations::TryGetFloat(lua_State* L, float* value)

{
	double val = 0;
	int sucess = LuaOperations::TryGetDouble(L, &val);
	*value = (float)val;
	return sucess;
}

int LuaOperations::TryGetInt(lua_State* L, int* value)

{
	double val = 0;
	int sucess = LuaOperations::TryGetDouble(L, &val);
	*value = (int)val;
	return sucess;
}

int LuaOperations::TryGetString(lua_State* L, std::string* value)

{
	if (!lua_isnil(L, -1) && lua_isstring(L, -1))
	{
		*value = lua_tostring(L, -1);
		lua_pop(L, 1);
		return 1;//Everything OK
	}
	*value = ' ';
	lua_pop(L, 1);
	return 0;//Value Nil or NAN
}

int LuaOperations::TryGetDoubleFromTable(lua_State* L, char* key, double* value)
{
	if (lua_gettop(L) < 1 || !lua_istable(L, -1))
	{
		*value = 0;
		return 0; //Stack contains no table
	}
	lua_pushstring(L, key); //Table Should already be on top
	lua_gettable(L, -2);
	return LuaOperations::TryGetDouble(L, value);
}


int LuaOperations::TryGetStringFromTable(lua_State* L, char* key, std::string* value)
{
	if (lua_gettop(L) < 1 || !lua_istable(L, -1))
	{
		*value = ' ';
		return 0; //Stack contains no table
	}
	lua_pushstring(L, key); //Table Should already be ón top
	lua_gettable(L, -2);
	return LuaOperations::TryGetString(L, value);
}


int LuaOperations::TryGetDoubleFromGlobal(lua_State* L, char* varName, double* value, bool throwError, std::string error)
{
	lua_getglobal(L, varName);
	if (!LuaOperations::TryGetDouble(L, value)) 
	{
		if (throwError)
		{
			lua_pushstring(L, error.c_str());
			lua_error(L);
		}
		return 0;
	}

	return 1;
}

int LuaOperations::TryGetStringFromGlobal(lua_State* L, char* varName, std::string* value, bool throwError /* = false */, std::string error /* = "Undefined Error" */)
{
	lua_getglobal(L, varName);
	if (!LuaOperations::TryGetString(L, value))
	{
		if (throwError)
		{
			lua_pushstring(L, error.c_str());
			lua_error(L);
		}
		return 0;
	}

	return 1;
}

int LuaOperations::TryGetFloatFromGlobal(lua_State* L, char* varName, float* value, bool throwError /* = false */, std::string error /* = "Undefined Error" */)
{
	double val = 0;
	int sucess = TryGetDoubleFromGlobal(L, varName, &val, throwError, error); //everything is double anyway
	*value = (float)val;
	return sucess;
}

int LuaOperations::TryGetIntFromGlobal(lua_State* L, char* varName, int* value, bool throwError /* = false */, std::string error /* = "Undefined Error" */)
{
	double val = 0;
	int sucess = TryGetDoubleFromGlobal(L, varName, &val, throwError, error); //everything is double anyway
	*value = (int)val;
	return sucess;
}

int LuaOperations::SaveLuaCall(lua_State* L, int args, int rets, bool throwLuaError, std::string errMsg)
{
	if (lua_pcall(L, args, rets, 0))
	{
		if (throwLuaError)
		{
			lua_pushstring(L,errMsg.c_str());
			lua_error(L);
		}
		return 1;
	}
	return 0;
}

int LuaOperations::TryGetFloatFromTable(lua_State* L, char* key, float* value)
{
	double val = 0;
	int sucess = TryGetDoubleFromTable(L, key, &val); //everything is double anyway
	*value = (float)val;
	return sucess;
}

int LuaOperations::TryGetIntFromTable(lua_State* L, char* key, int* value)
{
	double val = 0;
	int sucess = TryGetDoubleFromTable(L, key, &val); //everything is double anyway
	*value = (int)val;
	return sucess;
}


int LuaOperations::TableToVectors(lua_State* L, std::vector<std::string>* key, std::vector<std::string>* value)
{
	if (!lua_istable(L, -1))
		return 0;
	lua_pushnil(L);
	while (lua_next(L, -2))
	{
		key->push_back(lua_tostring(L, -2));
		value->push_back(lua_tostring(L, -1));
		lua_pop(L, 1);
	}
	return 1;
}

int LuaOperations::TableToVectors(lua_State* L, std::vector<std::string>* key, std::vector<double>* value)
{
	if (!lua_istable(L, -1))
		return 0;
	lua_pushnil(L);
	while (lua_next(L, -2))
	{
		key->push_back(lua_tostring(L, -2));
		value->push_back(lua_tonumber(L, -1));
		lua_pop(L, 1);
	}
	return 1;
}

int LuaOperations::TableToVector(lua_State* L, std::vector<std::string>* value)
{
	if (!lua_istable(L, -1))
		return 0;
	lua_pushnil(L);
	while (lua_next(L, -2))
	{
		value->push_back(lua_tostring(L, -1));
		lua_pop(L, 1);
	}
	return 1;
}

int LuaOperations::TableToVector(lua_State* L, std::vector<double>* value)
{
	if (!lua_istable(L, -1))
		return 0;
	lua_pushnil(L);
	while (lua_next(L, -2))
	{
		value->push_back(lua_tonumber(L, -1));
		lua_pop(L, 1);
	}
	return 1;
}

