#include "ScriptableLuaObject.h"
#include "FileLoader.h"
#include "lua.hpp"
#include <string>
#include <vector>
#include "LuaScriptStruct.h"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "LuaOperations.h"
#include "mge/core/World.hpp"
#include "mge/core/GameObject.hpp"
#include "LuaAPI.h"
#include "mge/core/AbstractGame.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/config.hpp"
#include "StaticBoxCollider.hpp"

static const luaL_reg level1API[]
{
	{"GetObject", LuaAPI::Lua_GetObject},
	{"Print", LuaAPI::Lua_WriteToConsole},
	{"SetPosition", LuaAPI::Lua_SetPosition},
	{"AddPosition", LuaAPI::Lua_AddPosition},
	{"GetPosition", LuaAPI::Lua_GetPosition},
	{"GetDistance", LuaAPI::Lua_GetDistance},
	{"CreateGameObject", LuaAPI::Lua_CreateGameObjectFromKey},
	{"GetParent", LuaAPI::Lua_GetParent},
	{"AddChild", LuaAPI::Lua_AddChild},
	{"CompareRef", LuaAPI::Lua_GameObjectEquals},
	//{"GameOver", LuaAPI::Lua_ResetGame},
	{NULL, NULL}

};



ScriptableLuaObject::ScriptableLuaObject(std::vector<std::string> attachedScripts)
{

	for each (std::string path in attachedScripts)
	{
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);

		luaL_openlib(L, "Game", level1API, 0);
		luaL_loadfile(L, path.c_str());
		LuaOperations::SaveLuaCall(L, 0, 0, true, "Could not run script " + path + '\n');
		//lua_call(L, 0, 0); //Compile and run the lua script

		_attachedScripts.push_back(L);
	}
	_scriptPath = attachedScripts;
}

void ScriptableLuaObject::OwnerChanged()
{
	for each (lua_State* L in _attachedScripts)
	{
		lua_getglobal(L, "initialize");

		GameObject** obj = (GameObject**)lua_newuserdata(L, sizeof(GameObject*));
		*obj = _owner;
		LuaOperations::SaveLuaCall(L, 1, 0, false);
	}
}

std::vector<LuaScriptStruct*> ScriptableLuaObject::_scripts = std::vector<LuaScriptStruct*>();

void ScriptableLuaObject::Initialize(std::string directory)
{

	for (std::string & path : FileLoader::GetFilesFromFolder(directory))
	{
		_scripts.push_back(new LuaScriptStruct(path));

	}
}


AbstractBehaviour* ScriptableLuaObject::Clone()
{
	return new ScriptableLuaObject(_scriptPath);
}

GameObject* ScriptableLuaObject::Instantiate(std::string key, GameObject* parent)
{



	for each (LuaScriptStruct* lss in _scripts)
	{
		if (lss->GetName() == key)
		{

			GameObject* object = new GameObject(lss->GetName(), lss->GetPosition());
			if (parent != NULL)
				parent->add(object);
			else
				AbstractGame::instance->_world->add(object);
			object->setMesh(lss->GetObject());
			object->setMaterial(new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + lss->GetTexturePath()), 2, 10, 0, 5, 2, Texture::load(config::MGE_TEXTURE_PATH+"height.png", true)));
			object->addBehaviour(new ScriptableLuaObject(lss->GetAttachedScripts()));
			if (lss->HasCollider())object->addBehaviour(new StaticBoxCollider(lss->GetColliderDimensions()));
			return object;
		}
	}
	return NULL;
}

void ScriptableLuaObject::update(float pTime)
{
	for each (lua_State* L in _attachedScripts)
	{
		lua_getglobal(L, "update");
		if (lua_isfunction(L, -1))
		{
			lua_pushnumber(L, pTime);
			LuaOperations::SaveLuaCall(L, 1, 0, false);
		}
		else
			lua_pop(L, -1); //Remove the thing we just added on the stack. it is for sure not a function.
	}
}



