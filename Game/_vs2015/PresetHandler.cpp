#include "PresetHandler.hpp"

PresetHandler* PresetHandler::instance = nullptr;
PresetHandler::PresetHandler(std::vector<std::string> files)
{
	instance = this;
	//Create One Gameobject by file
	std::vector<GameObject*> gobjs; //Pretend this is filled with gameobjects
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