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
	if (LuaOperations::SaveLuaCall(L, 0, 0))
	{
		return;
	}
	int l = lua_gettop(L);


	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "name", &_name))
	{
		std::cout << "This object has no name default name: NoNameObject\n";
		_name = "NoNameObject";
	}

	lua_getglobal(L, "AttachedScripts");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TableToVector(L, &_attachedScripts))
	{
		std::cout << "Object with key: "<< _name <<" has no scripts attached\n";
		_attachedScripts = std::vector<std::string>();
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "objPath", &_objPath))
	{
		std::cout << "Object with key: " << _name << " has no mesh\n";
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "texture", &_texturePath))
	{
		std::cout << "Object with key: " << _name << " has no texture\n";
	}
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "emissive", &_emmissiveTexture))
	{
		std::cout << "Object with key: " << _name << " has no emmissive map\n";
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "specular", &_specularTexture))
	{
		std::cout << "Object with key: " << _name << " has no specular map\n";
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "normal", &_normalTexture))
	{
		std::cout << "Object with key: " << _name << " has no normal map\n";
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetFloatFromTable(L, "posX", &_position.x))
	{
		std::cout << "Object with key: " << _name << " has no x coord. assuming 0\n";
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetFloatFromTable(L, "posY", &_position.y))
	{
		std::cout << "Object with key: " << _name << " has no y coord. assuming 0\n";
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetFloatFromTable(L, "posZ", &_position.z))
	{
		std::cout << "Object with key: " << _name << " has no z coord. assuming 0\n";
	}
	l = lua_gettop(L);

	_collider = glm::vec3(-1);

	lua_getglobal(L, "collider");
	if (!LuaOperations::TryGetFloatFromTable(L, "width", &_collider.x))
	{
		std::cout << "Object with key: " << _name << " has no collider.\n";
	}
	else
	{
		lua_getglobal(L, "collider");
		if (!LuaOperations::TryGetFloatFromTable(L, "height", &_collider.y))
		{
			std::cout << "Object with key: " << _name << " has no collider.\n";
		}
		else
		{
			lua_getglobal(L, "collider");
			if (!LuaOperations::TryGetFloatFromTable(L, "width", &_collider.z))
			{
				std::cout << "Object with key: " << _name << " has no collider.\n";
			}
		}
	}

	lua_close(L);

}

bool LuaScriptStruct::HasCollider()
{
	return _collider.x != 0;
}

glm::vec3 LuaScriptStruct::GetColliderDimensions()
{
	return _collider;
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

glm::vec3 LuaScriptStruct::GetPositionOffset()
{
	return _position;
}

std::string LuaScriptStruct::GetEmmissiveMap()
{
	return _emmissiveTexture;
}

std::string LuaScriptStruct::GetSpecular()
{
	return _specularTexture;
}

std::string LuaScriptStruct::GetNormal() {
	return _normalTexture;
}