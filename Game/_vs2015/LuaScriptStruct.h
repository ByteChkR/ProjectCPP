#ifndef LUASCRIPTSTRUCT_HPP

#define LUASCRIPTSTRUCT_HPP

#include <string>
#include <vector>
#include "mge/core/Mesh.hpp"
#include "glm.hpp"
#include "lua.hpp"
struct LuaScriptStruct
{
public:
	LuaScriptStruct(std::string filename);
	std::string GetName();
	std::string GetObjectPath();
	Mesh* GetObject();
	std::string GetTexturePath();
	glm::vec3 GetPosition();
	std::vector<std::string> GetAttachedScripts();

private:
	Mesh* _mesh;
	std::string _texturePath;
	std::string _objPath;
	std::string _name;
	glm::vec3 _position;
	std::vector<std::string> _attachedScripts;

};

#endif // !LUASCRIPTSTRUCT_HPP
