#ifndef PRESETHANDLER_HPP
#define PRESETHANDLER_HPP
#include <vector>
#include <string>
#include "mge/core/GameObject.hpp"
#include "ObjectPool.hpp"

class PresetHandler
{
public:
	PresetHandler(std::vector<std::string> files);
	~PresetHandler();
	GameObject* TakePreset(size_t index);
	void GivePreset(size_t index, GameObject* preset);
	int GetTotalInstances();
private:
	std::vector<ObjectPool<GameObject*>*> presets;
};

#endif // !PRESETHANDLER_HPP
