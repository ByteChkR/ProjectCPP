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

	int GetTotalBiomes();
	void GivePreset(int biomeID, size_t index, GameObject* preset);
	GameObject* TakePreset(int biomeID, size_t index);

private:
	std::vector<PresetHandler*> _presetHandlers;
};

#endif // !BIOME_HPP
