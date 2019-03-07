#include "LuaScriptStruct.h"
#include <string>
#include <vector>
#include "lua.hpp"
#include "LuaOperations.h"
#include "mge/core/Mesh.hpp"
#include <iostream>
#include "Debug.h"
#include "mge/core/AbstractGame.hpp"
LuaScriptStruct::LuaScriptStruct(std::string filename) :_mesh()
{
	isValid = false;
	lua_State* L = luaL_newstate();
	luaL_loadfile(L, filename.c_str());
	if (LuaOperations::SaveLuaCall(L, 0, 0))
	{
		Debug::LogError("Could not Load Object Script:" + filename + ".. Using Fallback Script");
		return;
	}
	int l = lua_gettop(L);


	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		Debug::LogError("Could not Load Object Script:" + filename + ".. Using Fallback Script");
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "name", &_name))
	{
		Debug::Log("This object has no name default name: NoNameObject", WARNINGS_ERRORS_LOG2);
		_name = "NoNameObject";
	}

	lua_getglobal(L, "AttachedScripts");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		Debug::LogError("Could not Load Object Script:" + filename + ".. Using Fallback Script");
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TableToVector(L, &_attachedScripts))
	{
		Debug::Log("Object with key: " + _name + " has no scripts attached", ALL);
		_attachedScripts = std::vector<std::string>();
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		Debug::LogError("Could not Load Object Script:" + filename + ".. Using Fallback Script");
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "objPath", &_objPath))
	{
		Debug::Log("Object with key: " + _name + " has no mesh", WARNINGS_ERRORS_LOG2);
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		Debug::LogError("Could not Load Object Script:" + filename + ".. Using Fallback Script");
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "texture", &_texturePath))
	{
		Debug::Log("Object with key: " + _name + " has no texture", WARNINGS_ERRORS_LOG2);
	}
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		Debug::LogError("Could not Load Object Script:" + filename + ".. Using Fallback Script");
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "emissive", &_emmissiveTexture))
	{
		Debug::Log("Object with key: " + _name + " has no emmissive map", WARNINGS_ERRORS_LOG2);
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		Debug::LogError("Could not Load Object Script:" + filename + ".. Using Fallback Script");
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "specular", &_specularTexture))
	{
		Debug::Log("Object with key: " + _name + " has no specular map", WARNINGS_ERRORS_LOG2);
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		Debug::LogError("Could not Load Object Script:" + filename + ".. Using Fallback Script");
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetStringFromTable(L, "normal", &_normalTexture))
	{
		Debug::Log("Object with key: " + _name + " has no normal map", WARNINGS_ERRORS_LOG2);
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		Debug::LogError("Could not Load Object Script:" + filename + ".. Using Fallback Script");
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetFloatFromTable(L, "posX", &_position.x))
	{
		Debug::Log("Object with key: " + _name + " has no x coord. assuming 0", WARNINGS_ERRORS_LOG2);
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		Debug::LogError("Could not Load Object Script:" + filename + ".. Using Fallback Script");
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetFloatFromTable(L, "posY", &_position.y))
	{
		Debug::Log("Object with key: " + _name + " has no y coord. assuming 0", WARNINGS_ERRORS_LOG2);
	}
	l = lua_gettop(L);
	lua_pop(L, 1);
	lua_getglobal(L, "GetMeta");
	if (LuaOperations::SaveLuaCall(L, 0, 1))
	{
		Debug::LogError("Could not Load Object Script:" + filename + ".. Using Fallback Script");
		return;
	}
	l = lua_gettop(L);
	if (!LuaOperations::TryGetFloatFromTable(L, "posZ", &_position.z))
	{
		Debug::Log("Object with key: " + _name + " has no z coord. assuming 0", WARNINGS_ERRORS_LOG2);
	}
	l = lua_gettop(L);

	_colliderMin = glm::vec3(-1);
	_colliderMax = glm::vec3(-1);
	hasCollider = true;

	lua_getglobal(L, "colliderMin");
	if (!LuaOperations::TryGetFloatFromTable(L, "width", &_colliderMin.x))
	{
		hasCollider = false;
		Debug::Log("Object with key: " + _name + " has no collider.", WARNINGS_ERRORS_LOG2);
	}
	else
	{
		lua_getglobal(L, "colliderMin");
		if (!LuaOperations::TryGetFloatFromTable(L, "height", &_colliderMin.y))
		{
			hasCollider = false;
			Debug::Log("Object with key: " + _name + " has no collider.", WARNINGS_ERRORS_LOG2);
		}
		else
		{
			lua_getglobal(L, "colliderMin");
			if (!LuaOperations::TryGetFloatFromTable(L, "depth", &_colliderMin.z))
			{
				hasCollider = false;
				Debug::Log("Object with key: " + _name + " has no collider.", WARNINGS_ERRORS_LOG2);
			}
		}
	}

	lua_getglobal(L, "colliderMax");
	if (!LuaOperations::TryGetFloatFromTable(L, "width", &_colliderMax.x))
	{
		hasCollider = false;
		Debug::Log("Object with key: " + _name + " has no collider.", WARNINGS_ERRORS_LOG2);
	}
	else
	{
		lua_getglobal(L, "colliderMax");
		if (!LuaOperations::TryGetFloatFromTable(L, "height", &_colliderMax.y))
		{
			hasCollider = false;
			Debug::Log("Object with key: " + _name + " has no collider.", WARNINGS_ERRORS_LOG2);
		}
		else
		{
			lua_getglobal(L, "colliderMax");
			if (!LuaOperations::TryGetFloatFromTable(L, "depth", &_colliderMax.z))
			{
				hasCollider = false;
				Debug::Log("Object with key: " + _name + " has no collider.", WARNINGS_ERRORS_LOG2);
			}
		}
	}
	std::string test;
	lua_getglobal(L, "colliderMode");
	if (LuaOperations::TryGetString(L, &test))
	{
		if (test == "auto")
		{
			Debug::Log("Auto Colliding Activated on script " + _name, ALL);
			hasCollider = true;
			autoCollider = true;
		}
		else
		{
			Debug::Log("Auto Colliding Dectivated on script " + _name, ALL);
			autoCollider = false;
		}
	}
	else
	{
		Debug::Log("Auto Colliding Dectivated on script " + _name, ALL);
		autoCollider = false;
	}

	lua_close(L);

	isValid = true; //Didnt return until now? NOICE
}

bool LuaScriptStruct::HasAutoCollider()
{
	return isValid ? autoCollider : AbstractGame::instance->sloFallback->autoCollider;
}


bool LuaScriptStruct::HasCollider()
{
	return isValid ? hasCollider : AbstractGame::instance->sloFallback->hasCollider;
}

glm::vec3 LuaScriptStruct::GetColliderMin()
{

	return isValid ? _colliderMin : AbstractGame::instance->sloFallback->_colliderMin;
}

glm::vec3 LuaScriptStruct::GetColliderMax()
{
	return isValid ? _colliderMax : AbstractGame::instance->sloFallback->_colliderMax;
}


std::vector<std::string> LuaScriptStruct::GetAttachedScripts()
{
	return isValid ? _attachedScripts : AbstractGame::instance->sloFallback->_attachedScripts;
}

std::string LuaScriptStruct::GetName()
{
	return isValid ? _name : AbstractGame::instance->sloFallback->_name;
}
std::string LuaScriptStruct::GetTexturePath()
{
	return isValid ? _texturePath : AbstractGame::instance->sloFallback->_texturePath;
}
std::string LuaScriptStruct::GetObjectPath()
{
	return isValid ? _objPath : AbstractGame::instance->sloFallback->_objPath;
}


Mesh* LuaScriptStruct::GetObject()
{
	if (_mesh != nullptr)return _mesh;
	return _mesh = Mesh::load(GetObjectPath());
}

glm::vec3 LuaScriptStruct::GetPositionOffset()
{
	return isValid ? _position : AbstractGame::instance->sloFallback->_position;
}

std::string LuaScriptStruct::GetEmmissiveMap()
{
	return isValid ? _emmissiveTexture : AbstractGame::instance->sloFallback->_emmissiveTexture;
}

std::string LuaScriptStruct::GetSpecular()
{
	return isValid ? _specularTexture : AbstractGame::instance->sloFallback->_specularTexture;
}

std::string LuaScriptStruct::GetNormal() {
	return isValid ? _normalTexture : AbstractGame::instance->sloFallback->_normalTexture;
}