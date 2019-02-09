#ifndef SCRIPTABLELUAOBJECT_HPP
#define SCRIPTABLELUAOBJECT_HPP

#include "lua.hpp"
#include <string>
#include <vector>
#include "LuaScriptStruct.h"
#include "mge/behaviours/AbstractBehaviour.hpp"

class ScriptableLuaObject : public AbstractBehaviour
{
public:
	static void Initialize(std::string dictionary);
	static void InitializeMaterials(std::string dictionary);
	static GameObject* Instantiate(std::string key, GameObject* parent = NULL);
	virtual void update(float pTime);

protected:
	virtual void OwnerChanged() override;

private:
	ScriptableLuaObject(std::vector<std::string> attachedScripts);
	static std::vector<LuaScriptStruct*> _scripts;
	std::vector<lua_State*> _attachedScripts = std::vector<lua_State*>();




};

#endif // !SCRIPTABLELUAOBJECT_HPP
