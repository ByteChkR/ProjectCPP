#include "LuaScriptStruct.h"
#include <string>
#include <vector>
#include "lua.hpp"
#include "LuaOperations.h"
#include "mge/core/Mesh.hpp"
#include <iostream>
LuaScriptStruct::LuaScriptStruct(std::string filename) :_mesh()
{
	lua_State* L = luaL_newstate();
	luaL_loadfile(L, filename.c_str());
	lua_call(L, 0, 0);
	int l = lua_gettop(L);
	lua_getglobal(L, "AttachedScripts");
	lua_call(L, 0, 1);
	l = lua_gettop(L);
	if (!LuaOperations::TableToVector(L, &_attachedScripts))
	{
		std::cout << "This object has no scripts attached";
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	lua_call(L, 0, 1);
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "name", &_name))
	{
		std::cout << "This object has no name";
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	lua_call(L, 0, 1);
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "objPath", &_objPath))
	{
		std::cout << "This object has no mesh";
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	lua_call(L, 0, 1);
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "texture", &_texturePath))
	{
		std::cout << "This object has no material";
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	lua_call(L, 0, 1);
	l = lua_gettop(L);
	if (!LuaOperations::TryGetFloatFromTable(L, "posX", &_position.x))
	{
		std::cout << "This object has no x coord. assuming 0";
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	lua_call(L, 0, 1);
	l = lua_gettop(L);
	if (!LuaOperations::TryGetFloatFromTable(L, "posX", &_position.y))
	{
		std::cout << "This object has no y coord. assuming 0";
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	lua_call(L, 0, 1);
	l = lua_gettop(L);
	if (!LuaOperations::TryGetFloatFromTable(L, "posX", &_position.z))
	{
		std::cout << "This object has no z coord. assuming 0";
	}
	l = lua_gettop(L);
	lua_close(L);
	_position = glm::vec3(0, 50, 0);

}


std::vector<std::string> LuaScriptStruct::GetAttachedScripts()
{
	return _attachedScripts;
}

std::string LuaScriptStruct::GetName()
{
	return _name;
}
std::string LuaScriptStruct::GetTexturePath()
{
	return _texturePath;
}
std::string LuaScriptStruct::GetObjectPath()
{
	return _objPath;
}


Mesh* LuaScriptStruct::GetObject()
{
	if (_mesh != nullptr)return _mesh;
	return _mesh = Mesh::load(_objPath);
}

glm::vec3 LuaScriptStruct::GetPosition()
{
	return _position;
}
