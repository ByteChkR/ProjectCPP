#include "PresetHandler.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "StaticBoxCollider.hpp"

PresetHandler::~PresetHandler()
{
	for each (ObjectPool<GameObject*>* op in presets)
	{
		//delete op;
		op = nullptr;
	}
}

PresetHandler::PresetHandler(std::vector<GameObject*> gobjs)
{
	//Create One Gameobject by file

	//SERIALIZATION MISSING


	//GameObject* zero = new GameObject("zero");
	//GameObject* one = new GameObject("one"); 
	//GameObject* three = new GameObject("three");
	//GameObject* four = new GameObject("four");
	//
	
	//GameObject* two = new GameObject("two");
	//Mesh* m = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");
	//Mesh* m1 = Mesh::load(config::MGE_MODEL_PATH + "cylinder_smooth.obj");
	//Mesh* m2 = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");
	//Mesh* m3 = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

	//AbstractMaterial* mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"), 2, 10, 0.7, 1, 1);
	//AbstractMaterial* mat1 = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"), 2, 10, 1, 1, 10);
	//AbstractMaterial* mat2 = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"), 2, 10, 1, 1, 10);
	//AbstractMaterial* mat3 = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"), 2, 10, 1, 1, 10);
	//one->addBehaviour(sbc);
	//two->addBehaviour(sbc->Clone());
	//three->addBehaviour(sbc->Clone());
	//four->addBehaviour(sbc->Clone());
	//one->setMaterial(mat);
	//two->setMaterial(mat1);
	//three->setMaterial(mat2);
	//four->setMaterial(mat3);
	//one->setMesh(m1);
	//two->setMesh(m);
	//three->setMesh(m);
	//four->setMesh(m);
	//gobjs.push_back(zero);
	//gobjs.push_back(one);
	//gobjs.push_back(two);
	//gobjs.push_back(three);
	//gobjs.push_back(four);


	presets = std::vector<ObjectPool<GameObject*>*>();
	for each (GameObject* g in gobjs)
	{
		
		presets.push_back(new ObjectPool<GameObject*>(g));
	}

}

int PresetHandler::GetTotalInstances()
{
	int count = 0;
	for each (ObjectPool<GameObject*>* op in presets)
	{
		count += op->TotalInstances();
	}
	return count;
}

int PresetHandler::GetTotalActiveInstances()
{
	int count = 0;
	for each (ObjectPool<GameObject*>* op in presets)
	{
		count += op->TotalActiveInstances();
	}
	return count;
}


void PresetHandler::GivePreset(size_t index, GameObject* preset)
{
	if (index >= presets.size())return;
	preset->setLocalPosition(glm::vec3(0, 50, 0));
	presets[index]->Give(preset);
}

GameObject* PresetHandler::TakePreset(size_t index)
{
	if (index >= presets.size())return nullptr;
	return presets[index]->Take();
}