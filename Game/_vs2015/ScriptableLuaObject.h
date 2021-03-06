#ifndef SCRIPTABLELUAOBJECT_HPP
#define SCRIPTABLELUAOBJECT_HPP

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

class ScriptableLuaObject : public AbstractBehaviour
{
public:
	static void Initialize(std::string dictionary);
	static GameObject* Instantiate(std::string key, GameObject* parent = NULL);
	static LuaScriptStruct* GetStructWithName(std::string name);
	virtual void update(float pTime);
	virtual AbstractBehaviour* Clone() override;
	glm::vec3 GetLuaOffset();
protected:
	virtual void OwnerChanged() override;

private:
	LuaScriptStruct* _lss;
	ScriptableLuaObject(LuaScriptStruct* lss);
	static std::vector<LuaScriptStruct*> _scripts;
	std::vector<std::string> _scriptPath = std::vector<std::string>();
	std::vector<lua_State*> _attachedScripts = std::vector<lua_State*>();




};

#endif // !SCRIPTABLELUAOBJECT_HPP
