#include "LuaScriptStruct.h"
#include <string>
#include <vector>
#include "lua.hpp"
#include "LuaOperations.h"
#include "mge/core/Mesh.hpp"
#include <iostream>
#include "Debug.h"
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
		Debug::Log("This object has no name default name: NoNameObject");
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
		Debug::Log("Object with key: " + _name + " has no scripts attached");
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
		Debug::Log("Object with key: " + _name + " has no mesh");
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
		Debug::Log("Object with key: " + _name + " has no texture");
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
		Debug::Log( "Object with key: " + _name + " has no emmissive map");
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
		Debug::Log("Object with key: " + _name + " has no specular map");
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
		Debug::Log("Object with key: " + _name + " has no normal map");
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
		Debug::Log("Object with key: " + _name + " has no x coord. assuming 0");
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
		Debug::Log("Object with key: " + _name + " has no y coord. assuming 0");
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
		Debug::Log("Object with key: " + _name + " has no z coord. assuming 0");
	}
	l = lua_gettop(L);

	_colliderMin = glm::vec3(-1);
	_colliderMax = glm::vec3(-1);
	hasCollider = true;

	lua_getglobal(L, "colliderMin");
	if (!LuaOperations::TryGetFloatFromTable(L, "width", &_colliderMin.x))
	{
		hasCollider = false;
		Debug::Log("Object with key: " + _name + " has no collider.");
	}
	else
	{
		lua_getglobal(L, "colliderMin");
		if (!LuaOperations::TryGetFloatFromTable(L, "height", &_colliderMin.y))
		{
			hasCollider = false; 
			Debug::Log("Object with key: " + _name + " has no collider.");
		}
		else
		{
			lua_getglobal(L, "colliderMin");
			if (!LuaOperations::TryGetFloatFromTable(L, "depth", &_colliderMin.z))
			{
				hasCollider = false;
				Debug::Log("Object with key: " + _name + " has no collider.");
			}
		}
	}

	lua_getglobal(L, "colliderMax");
	if (!LuaOperations::TryGetFloatFromTable(L, "width", &_colliderMax.x))
	{
		hasCollider = false;
		Debug::Log("Object with key: " + _name + " has no collider.");
	}
	else
	{
		lua_getglobal(L, "colliderMax");
		if (!LuaOperations::TryGetFloatFromTable(L, "height", &_colliderMax.y))
		{
			hasCollider = false;
			Debug::Log("Object with key: " + _name + " has no collider.");
		}
		else
		{
			lua_getglobal(L, "colliderMax");
			if (!LuaOperations::TryGetFloatFromTable(L, "depth", &_colliderMax.z))
			{
				hasCollider = false;
				Debug::Log("Object with key: " + _name + " has no collider.");
			}
		}
	}
	std::string test;
	lua_getglobal(L, "colliderMode");
	if (LuaOperations::TryGetString(L, &test))
	{
		if (test == "auto")
		{
			Debug::Log("Auto Colliding Activated on script " + _name);
			hasCollider = true;
			autoCollider = true;
		}
		else
		{
			Debug::Log("Auto Colliding Dectivated on script " + _name);
			autoCollider = false;
		}
	}
	else
	{
		Debug::Log("Auto Colliding Dectivated on script " + _name);
		autoCollider = false;
	}

	lua_close(L);

}

bool LuaScriptStruct::HasAutoCollider()
{
	return autoCollider;
}


bool LuaScriptStruct::HasCollider()
{
	return hasCollider;
}

glm::vec3 LuaScriptStruct::GetColliderMin()
{

	return _colliderMin;
}

glm::vec3 LuaScriptStruct::GetColliderMax()
{
	return _colliderMax;
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