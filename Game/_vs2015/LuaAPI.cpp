#include "LuaAPI.h"
#include "mge/core/GameObject.hpp"
#include "LuaOperations.h"
#include "mge/core/World.hpp"
#include <vector>
#include <string>
#include "ScriptableLuaObject.h"
#include "mge/core/AbstractGame.hpp"
#include "lua.hpp"

int LuaAPI::Lua_AddChild(lua_State* L)
{
	if (!lua_isuserdata(L, 1)) {
		lua_pushstring(L, "Set Position can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}
	GameObject** parent = (GameObject**)lua_touserdata(L, 1);
	if (!lua_isuserdata(L, 2)) {
		lua_pushstring(L, "Set Position can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}
	GameObject** child = (GameObject**)lua_touserdata(L, 2);

	(*parent)->add((*child));

}

int LuaAPI::Lua_GameObjectEquals(lua_State* L)
{
	if (!lua_isuserdata(L, 1)) {
		lua_pushstring(L, "Set Position can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}
	GameObject** left = (GameObject**)lua_touserdata(L, 1);
	if (!lua_isuserdata(L, 2)) {
		lua_pushstring(L, "Set Position can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}

	GameObject** right = (GameObject**)lua_touserdata(L, 2);

	lua_pushboolean(L, (*right) == (*left));

	return 1;

}

int LuaAPI::Lua_GetParent(lua_State* L)
{
	if (!lua_isuserdata(L, 1)) {
		lua_pushstring(L, "Set Position can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}
	GameObject** pptr = (GameObject**)lua_touserdata(L, 1);
	GameObject* parent = (*pptr)->getParent();
	if (parent == nullptr)
		lua_pushnil(L);
	else
	{

		GameObject** g = (GameObject**)lua_newuserdata(L, sizeof(GameObject*));
		(*g) = parent;
	}
	return 1;

}

int LuaAPI::Lua_AddPosition(lua_State* L)
{
	if (!lua_isuserdata(L, 1)) {
		lua_pushstring(L, "Add Position can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}
	GameObject** pptr = (GameObject**)lua_touserdata(L, 1);
	glm::vec3 pos = glm::vec3();
	if (!LuaOperations::TryGetFloat(L, &pos.z))
	{
		lua_pushstring(L, "Z Value not specified");
		lua_error(L);
	}
	if (!LuaOperations::TryGetFloat(L, &pos.y))
	{
		lua_pushstring(L, "Y Value not specified");
		lua_error(L);
	}

	if (!LuaOperations::TryGetFloat(L, &pos.x))
	{
		lua_pushstring(L, "X Value not specified");
		lua_error(L);
	}

	(*pptr)->setLocalPosition((*pptr)->getLocalPosition() + pos);
}

int LuaAPI::Lua_GetObject(lua_State* L)
{
	std::string objName;
	if (!LuaOperations::TryGetString(L, &objName))
	{
		lua_pushstring(L, "Could not read argument 1. it should be a string");
		lua_error(L);
		//Error
	}

	GameObject* obj = AbstractGame::instance->_world->FindInChildren(objName);
	if (obj != NULL)
	{
		GameObject** g = (GameObject**)lua_newuserdata(L, sizeof(GameObject*));
		*g = obj;
	}
	else {
		lua_pushnil(L);
	}
	return 1;
}

int LuaAPI::Lua_CreateGameObjectFromKey(lua_State* L) {
	std::string key;
	if (!LuaOperations::TryGetString(L, &key))
	{
		//Error
	}
	GameObject* obj = ScriptableLuaObject::Instantiate(key);
	GameObject** g = (GameObject**)lua_newuserdata(L, sizeof(GameObject*));
	*g = obj;
	return 1;
}

int LuaAPI::Lua_WriteToConsole(lua_State* L)
{
	int l = lua_gettop(L);
	std::string txt;
	if (!LuaOperations::TryGetString(L, &txt))
	{
		lua_pushstring(L, "Could not read argument 1. it should be a string");
		lua_error(L);
		//Error
	}
	l = lua_gettop(L);
	return 0;
}

int LuaAPI::Lua_GetPosition(lua_State* L)
{
	int l = lua_type(L, -1);
	if (!lua_isuserdata(L, -1)) {
		lua_pushstring(L, "Get Position can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}

	GameObject** pptr = (GameObject**)lua_touserdata(L, -1);
	GameObject* test = *pptr;

	lua_pushnumber(L, test->getLocalPosition().z);
	lua_pushnumber(L, test->getLocalPosition().y);
	lua_pushnumber(L, test->getLocalPosition().x);
	return 3;
}

int LuaAPI::Lua_SetPosition(lua_State* L)
{

	int l = lua_gettop(L);
	if (!lua_isuserdata(L, 1)) {
		lua_pushstring(L, "Set Position can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}

	GameObject** pptr = (GameObject**)lua_touserdata(L, 1);
	l = lua_gettop(L);
	glm::vec3 pos = glm::vec3();
	if (!LuaOperations::TryGetFloat(L, &pos.z))
	{
		lua_pushstring(L, "Z Value not specified");
		lua_error(L);
	}

	l = lua_gettop(L);
	if (!LuaOperations::TryGetFloat(L, &pos.y))
	{
		lua_pushstring(L, "Y Value not specified");
		lua_error(L);
	}

	if (!LuaOperations::TryGetFloat(L, &pos.x))
	{
		lua_pushstring(L, "X Value not specified");
		lua_error(L);
	}
	//lua_pop(L, -1);
	(*pptr)->setLocalPosition(pos);

	return 0;
}




int LuaAPI::Lua_GetDistance(lua_State* L)
{
	if (!lua_isuserdata(L, -1) || !lua_isuserdata(L, -2))
	{
		lua_pushstring(L, "Error, one of the object references is not valid");
		lua_error(L);
	}
	GameObject** pptr1 = (GameObject**)lua_touserdata(L, -1);
	GameObject** pptr2 = (GameObject**)lua_touserdata(L, -2);
	glm::vec3 p1, p2;
	p1 = (*pptr1)->getWorldPosition();
	p2 = (*pptr2)->getWorldPosition();

	float d = glm::distance(p1, p2);
	int i = lua_gettop(L);
	lua_pop(L, -1);

	lua_pushnumber(L, d);
	return 1;

}