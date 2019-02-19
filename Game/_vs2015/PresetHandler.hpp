#ifndef PRESETHANDLER_HPP
#define PRESETHANDLER_HPP
#include <vector>
#include <string>
#include "mge/core/GameObject.hpp"
#include "ObjectPool.hpp"

class PresetHandler
{
public:
	PresetHandler(std::vector<GameObject*> gobjs);
	~PresetHandler();
	void Unload();
	GameObject* TakePreset(size_t index);
	void GivePreset(size_t index, GameObject* preset);
	int GetTotalInstances();
	int GetTotalActiveInstances();
private:
	std::vector<ObjectPool<GameObject*>*> presets;
};

#endif // !PRESETHANDLER_HPP
