#ifndef BIOME_HPP

#define BIOME_HPP

#include "mge/core/GameObject.hpp"
#include <vector>
#include "../_vs2015/PresetHandler.hpp"

class Biome
{
public:


	Biome(std::string pLuaFile);
	~Biome();

	void GivePreset(size_t index, GameObject* preset);
	GameObject* TakePreset(size_t index);
	int GetTotalInstances();

private:
	PresetHandler* _handler;
};

#endif // !BIOME_HPP
