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
	GameObject* TakePreset(int index);
	void GivePreset(int index, GameObject* preset);
private:
	std::vector<ObjectPool<GameObject*>*> presets;
};

#endif // !PRESETHANDLER_HPP
