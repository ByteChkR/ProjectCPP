#include "PresetHandler.hpp"


PresetHandler::PresetHandler(std::vector<std::string> files)
{
	//Create One Gameobject by file
	std::vector<GameObject*> gobjs; //Pretend this is filled with gameobjects
	presets = std::vector<ObjectPool<GameObject*>*>();
	for each (GameObject* g in gobjs)
	{
		presets.push_back(new ObjectPool<GameObject*>(g));

	}

}

void PresetHandler::GivePreset(int index, GameObject* preset)
{
	if (index >= presets.size())return;
	presets[index]->Give(preset);
}

GameObject* PresetHandler::TakePreset(int index)
{
	if (index >= presets.size())return;
	return presets[index]->Take();
}