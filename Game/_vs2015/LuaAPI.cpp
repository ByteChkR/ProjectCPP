#include "LuaAPI.h"
#include "mge/core/GameObject.hpp"
#include "LuaOperations.h"
#include "mge/core/World.hpp"
#include <vector>
#include <string>
#include "ScriptableLuaObject.h"
#include "mge/core/AbstractGame.hpp"
#include "lua.hpp"
#include "MapBuilder.h"
#include "mge/util/AudioManager.h"
#include "LevelManager.h"
#include "mge/materials/AnimationMaterial.hpp"
#include "../_vs2015/Debug.h"
int LuaAPI::Lua_PlayMusic(lua_State* L)
{
	double nr = 0;
	if (!LuaOperations::TryGetDouble(L, &nr))
	{
		lua_pushstring(L, "Could not read the music number."); //Push error.
		lua_error(L);
		return 1;
	}
	else
		AudioManager::instance->ChangeBackgroundMusic((int)nr);//If it worked we play the sound(or we try)
	return 0; //We return nothing if it worked

}

int LuaAPI::Lua_PlaySound(lua_State* L)
{
	double nr = 0;
	if (!LuaOperations::TryGetDouble(L, &nr))
	{
		lua_pushstring(L, "Could not read the sound number."); //Push error.
		lua_error(L);
		return 1;
	}
	else
		AudioManager::instance->PlaySound((int)nr);//If it worked we play the sound(or we try)
	return 0; //We return nothing if it worked

}

int LuaAPI::Lua_GetCurrentLevelProgress(lua_State* L)
{
	if (MapBuilder::instance != nullptr)
	{
		lua_pushnumber(L, MapBuilder::instance->GetProgress());
		return 1;
	}
	else
	{
		lua_pushstring(L, "There was no level initialized.");
		lua_error(L);
		return 1;
	}
}

int LuaAPI::Lua_GetCurrentLevel(lua_State* L)
{
	if (MapBuilder::instance != nullptr)
	{
		lua_pushnumber(L, LevelManager::instance->GetCurrent());
		return 1;
	}
	else
	{
		lua_pushstring(L, "There was no level manager initialized.");
		lua_error(L);
		return 1;
	}
}

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
	return 0;

}

int LuaAPI::Lua_NextAnimationFrame(lua_State* L)
{
	if (!lua_isuserdata(L, 1))
	{
		lua_pushstring(L, "NextAnimationFrame can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}
	else
	{
		GameObject** obj = (GameObject**)lua_touserdata(L, 1);
		AnimationMaterial* am;
		if ((am = dynamic_cast<AnimationMaterial*>((*obj)->getMaterial())) != nullptr)
		{
			am->NextFrame();
			return 0;
		}
		else
		{

			lua_pushstring(L, "NextAnimationFrame can only be called with a valid object reference that has a AnimationMaterial Attached.");
			lua_error(L);
			return 1;
		}
	}
}

int LuaAPI::Lua_GetCurrentAnimationFrame(lua_State* L)
{
	if (!lua_isuserdata(L, 1))
	{
		lua_pushstring(L, "GetAnimationFrame can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}
	else
	{
		GameObject** obj = (GameObject**)lua_touserdata(L, 1);
		AnimationMaterial* am;
		if ((am = dynamic_cast<AnimationMaterial*>((*obj)->getMaterial())) != nullptr)
		{
			lua_pushnumber(L, am->GetCurrentFrameNum());
			return 1;
		}
		else
		{
			lua_pushstring(L, "GetAnimationFrame can only be called with a valid object reference that contains an AnimationMaterial");
			lua_error(L);
			return 1;
		}
	}
}

int LuaAPI::Lua_StopParticleEffect(lua_State* L)
{
	if (!lua_isuserdata(L, 1))
	{
		lua_pushstring(L, "StopParticleEffect can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}
	else
	{
		GameObject** obj = (GameObject**)lua_touserdata(L, 1);
		ParticleEmitter* am;
		if ((am = dynamic_cast<ParticleEmitter*>((*obj)->getMaterial())) != nullptr)
		{
			am->Stop();
			return 0;
		}
		else
		{
			lua_pushstring(L, "StopParticleEffect can only be called with a valid object reference that contains an ParticleEmitter");
			lua_error(L);
			return 1;
		}
	}
}

int LuaAPI::Lua_StopParticleEffectImmediate(lua_State* L)
{
	if (!lua_isuserdata(L, 1))
	{
		lua_pushstring(L, "StopParticleEffec can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}
	else
	{
		GameObject** obj = (GameObject**)lua_touserdata(L, 1);
		ParticleEmitter* am;
		if ((am = dynamic_cast<ParticleEmitter*>((*obj)->getMaterial())) != nullptr)
		{
			am->Stop(true);
			return 1;
		}
		else
		{
			lua_pushstring(L, "StopParticleEffec can only be called with a valid object reference that contains an ParticleEmitter");
			lua_error(L);
			return 1;
		}
	}
}

int LuaAPI::Lua_PlayParticleEffect(lua_State* L)
{
	if (!lua_isuserdata(L, 1))
	{
		lua_pushstring(L, "StopParticleEffec can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}
	else
	{
		GameObject** obj = (GameObject**)lua_touserdata(L, 1);
		ParticleEmitter* am;
		if ((am = dynamic_cast<ParticleEmitter*>((*obj)->getMaterial())) != nullptr)
		{
			am->Start();
			return 0;
		}
		else
		{
			lua_pushstring(L, "StopParticleEffec can only be called with a valid object reference that contains an ParticleEmitter");
			lua_error(L);
			return 1;
		}
	}
}

int LuaAPI::Lua_ChangeAnimationFrame(lua_State* L)
{
	if (!lua_isuserdata(L, 1))
	{
		lua_pushstring(L, "ChangeAnimationFrame can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}
	else
	{
		GameObject** obj = (GameObject**)lua_touserdata(L, 1);
		AnimationMaterial* am;
		if ((am = dynamic_cast<AnimationMaterial*>((*obj)->getMaterial())) != nullptr)
		{
			double framenum;
			if (!LuaOperations::TryGetDouble(L, &framenum))
			{
				lua_pushstring(L, "Could not get the frame number. Is it a number?");
				lua_error(L);
				return 1;
			}
			am->SetFrame((int)framenum);
			return 0;
		}
		else
		{

			lua_pushstring(L, "NextAnimationFrame can only be called with a valid object reference that has a AnimationMaterial Attached.");
			lua_error(L);
			return 1;
		}
	}
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
		lua_pushstring(L, "GetParent can only be called with a valid object reference");
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
	return 0;
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
		lua_pushstring(L, "Could not read argument 1. it should be a string");
		lua_error(L);
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
		return 1;
	}
	Debug::Log("Lua Script Console: " + txt );
	l = lua_gettop(L);
	return 0;
}

int LuaAPI::Lua_GetPosition(lua_State* L)
{
	int l = lua_type(L, -1);
	if (!lua_isuserdata(L, -1)) {
		lua_pushstring(L, "Get Position can only be called with a valid object reference");
		Debug::LogError("Lua ERROR: Get Position can only be called with a valid object reference");
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
		Debug::LogError("Lua ERROR: Set Position can only be called with a valid object reference");
		lua_error(L);
		return 1;
	}

	GameObject** pptr = (GameObject**)lua_touserdata(L, 1);
	l = lua_gettop(L);
	glm::vec3 pos = glm::vec3();
	if (!LuaOperations::TryGetFloat(L, &pos.z))
	{
		lua_pushstring(L, "Z Value not specified"); 
		Debug::LogError("Lua ERROR: Z Value not specified");
		lua_error(L);
	}

	l = lua_gettop(L);
	if (!LuaOperations::TryGetFloat(L, &pos.y))
	{
		lua_pushstring(L, "Y Value not specified");
		Debug::LogError("Lua ERROR: Y Value not specified");
		lua_error(L);
	}

	if (!LuaOperations::TryGetFloat(L, &pos.x))
	{
		lua_pushstring(L, "X Value not specified"); 
		Debug::LogError("Lua ERROR: X Value not specified");
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
		Debug::LogError("Lua ERROR: Error, one of the object references is not valid");
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