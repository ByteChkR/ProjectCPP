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
	glm::vec3 GetPositionOffset();
	std::vector<std::string> GetAttachedScripts();
	bool HasCollider();
	glm::vec3 GetColliderMin();
	glm::vec3 GetColliderMax();
	std::string GetEmmissiveMap();

	std::string GetSpecular();
	std::string GetNormal();
	bool HasAutoCollider();
	
private:
	Mesh* _mesh;
	std::string _texturePath;
	std::string _emmissiveTexture;
	std::string _specularTexture;
	std::string _normalTexture;
	std::string _objPath;
	std::string _name;
	glm::vec3 _position;
	std::vector<std::string> _attachedScripts;
	glm::vec3 _colliderMin;
	glm::vec3 _colliderMax;
	bool hasCollider;
	bool autoCollider;
	bool isValid;
};

#endif // !LUASCRIPTSTRUCT_HPP
