#ifndef LUAAPI_HPP

#define LUAAPI_HPP
#include "lua.hpp"
class LuaAPI
{
public:

#pragma region Game
	//static int Lua_NextLevel(lua_State* L);
#pragma endregion

#pragma region ObjectHandling
	static int Lua_CreateGameObjectFromKey(lua_State* L);
	static int Lua_GetObject(lua_State* L);
	static int Lua_GetParent(lua_State* L);
	static int Lua_GameObjectEquals(lua_State* L);
	static int Lua_AddChild(lua_State* L);
	//static int Lua_RemoveChild(lua_State* L);
	//static int Lua_GetWorld(lua_State* L);
	//static int Lua_AddBehaviour(lua_State* L);
	//static int Lua_RemoveBehaviour(lua_State* L);
#pragma endregion

#pragma region Movement
	static int Lua_GetPosition(lua_State* L);
	static int Lua_GetDistance(lua_State* L);
	static int Lua_SetPosition(lua_State* L);
	static int Lua_AddPosition(lua_State* L);
	//static int Lua_SetRotation(lua_State* L);
	//static int Lua_GetRotation(lua_State* L);
	//static int Lua_AddRotation(lua_State* L);
#pragma endregion

#pragma region Math

	//static int Lua_Sin(lua_State* L);
	//static int Lua_Cos(lua_State* L);
	//static int Lua_Pow(lua_State* L);
	//static int Lua_IntPow(lua_State* L);
	//static int Lua_Lerp(lua_State* L);
	//static int Lua_GetObjectsInRange(lua_State* L);
#pragma endregion

#pragma region Debug
	static int Lua_WriteToConsole(lua_State* L);
#pragma endregion
};

#endif // !LUAAPI_HPP
