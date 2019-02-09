#include "mge/util/Biome.h"

#include <fstream>
#include <iostream>
#include "..\_vs2015\ScriptableLuaObject.h"
#include "..\_vs2015\LuaOperations.h"

Biome::Biome(std::string pLuaFile)
{
	std::vector<GameObject*> objs = std::vector<GameObject*>();
	std::vector<std::string> objKeys = std::vector<std::string>();
	lua_State* ls = luaL_newstate();
	luaL_loadfile(ls, pLuaFile.c_str());
	LuaOperations::SaveLuaCall(ls, 0, 0, true, "Could not read biome file " + pLuaFile + '\n');

	lua_getglobal(ls, "objects");

	if (LuaOperations::TableToVector(ls, &objKeys) == 0) {
		lua_pushstring(ls, ("Error reading biome data " + pLuaFile).c_str());
		lua_error(ls);
		throw;
	}

	for (size_t i = 0; i < objKeys.size(); i++)
	{
		objs.push_back(ScriptableLuaObject::Instantiate(objKeys[i]));
		objs[i]->setLocalPosition(glm::vec3(0, 0, 50)); //Move the originals out of sight.
	}



	//lua load file
	//lua_global




	_handler = new PresetHandler(objs);
}

Biome::~Biome()
{

}

int Biome::GetTotalInstances()
{
	return _handler->GetTotalInstances();
}

GameObject* Biome::TakePreset(size_t index)
{
	return _handler->TakePreset(index);
}

void Biome::GivePreset(size_t index, GameObject* obj)
{
	_handler->GivePreset(index, obj);
}