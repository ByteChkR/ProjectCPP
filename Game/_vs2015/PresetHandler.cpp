#include "PresetHandler.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
PresetHandler* PresetHandler::instance = nullptr;
PresetHandler::PresetHandler(std::vector<std::string> files)
{
	instance = this;
	//Create One Gameobject by file

	//SERIALIZATION MISSING

	std::vector<GameObject*> gobjs; //Pretend this is filled with gameobjects

	GameObject* zero = new GameObject("zero");
	GameObject* one = new GameObject("one"); 
	GameObject* three = new GameObject("three");
	GameObject* four = new GameObject("four");
	
	GameObject* two = new GameObject("two");
	Mesh* m = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");
	AbstractMaterial* mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"), 2, 10);
	AbstractMaterial* mat1 = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"), 2, 10);
	AbstractMaterial* mat2 = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"), 2, 10);
	AbstractMaterial* mat3 = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"), 2, 10);
	one->setMaterial(mat);
	two->setMaterial(mat1);
	three->setMaterial(mat2);
	four->setMaterial(mat3);
	one->setMesh(m);
	two->setMesh(m);
	three->setMesh(m);
	four->setMesh(m);
	gobjs.push_back(zero);
	gobjs.push_back(one);
	gobjs.push_back(two);
	gobjs.push_back(three);
	gobjs.push_back(four);


	presets = std::vector<ObjectPool<GameObject*>*>();
	for each (GameObject* g in gobjs)
	{
		presets.push_back(new ObjectPool<GameObject*>(g));

	}

}

void PresetHandler::GivePreset(size_t index, GameObject* preset)
{
	if (index >= presets.size())return;
	preset->setLocalPosition(glm::vec3(0, 0, -50));
	presets[index]->Give(preset);
}

GameObject* PresetHandler::TakePreset(size_t index)
{
	if (index >= presets.size())return nullptr;
	return presets[index]->Take();
}