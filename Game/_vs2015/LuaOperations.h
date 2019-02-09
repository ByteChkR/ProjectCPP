#ifndef LUAOPERATIONS_HPP
#define LUAOPERATIONS_HPP

#include "lua.h"
#include <vector>
#include <string>
class LuaOperations
{
private:
	LuaOperations();

public:
	static int TryGetString(lua_State* L, std::string* value);
	static int TryGetFloat(lua_State* L, float* value);
	static int TryGetInt(lua_State* L, int* value);
	static int TryGetDouble(lua_State* L, double* value);
	static int TryGetIntFromTable(lua_State* L, char* key, int* value);
	static int TryGetFloatFromTable(lua_State* L, char* key, float* value);
	static int TryGetDoubleFromTable(lua_State* L, char* key, double* value);
	static int TryGetStringFromTable(lua_State* L, char* key, std::string* value);
	//static int TableValuesToVector(lua_State* L, std::vector<std::string>* value);
	//static int TableValuesToVector(lua_State* L, std::vector<double>* value);
	//static int TableKeysToVector(lua_State* L, std::vector<std::string>* value);
	static int TableToVectors(lua_State* L, std::vector<std::string>* key, std::vector<std::string>* value);
	static int TableToVectors(lua_State* L, std::vector<std::string>* key, std::vector<double>* value);
	static int TableToVector(lua_State* L, std::vector<std::string>* value);
	static int TableToVector(lua_State* L, std::vector<double>* value);
};

#endif // !LUAOPERATIONS_HPP
