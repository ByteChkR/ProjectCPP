#include "PresetHandler.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
PresetHandler* PresetHandler::instance = nullptr;
PresetHandler::PresetHandler(std::vector<std::string> files)
{
	instance = this;
	//Create One Gameobject by file

	//SERIALIZATION MISSING

	std::vector<GameObject*> gobjs; //Pretend this is filled with gameobjects

	GameObject* zero = new GameObject("");
	GameObject* one = new GameObject("");
	
	GameObject* two = new GameObject("");
	Mesh* m = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");
	AbstractMaterial* mat = new ColorMaterial(glm::vec3(1, 0, 0));
	AbstractMaterial* mat1 = new ColorMaterial(glm::vec3(0, 1, 0));
	one->setMaterial(mat);
	two->setMaterial(mat1);
	one->setMesh(m);
	two->setMesh(m);
	gobjs.push_back(zero);
	gobjs.push_back(one);
	gobjs.push_back(two);


	presets = std::vector<ObjectPool<GameObject*>*>();
	for each (GameObject* g in gobjs)
	{
		presets.push_back(new ObjectPool<GameObject*>(g));

	}

}

void PresetHandler::GivePreset(size_t index, GameObject* preset)
{
	if (index >= presets.size())return;
	presets[index]->Give(preset);
}

GameObject* PresetHandler::TakePreset(size_t index)
{
	if (index >= presets.size())return nullptr;
	return presets[index]->Take();
}