#ifndef BIOMEHANDLER_HPP

#define BIOMEHANDLER_HPP

#include "mge/core/GameObject.hpp"
#include <vector>
#include "../_vs2015/PresetHandler.hpp"

class BiomeHandler
{
public:
	static BiomeHandler* instance;
	//biomes[i][j] = Single Obstacle;  i = biomeID ; j = obstacleType
	BiomeHandler(std::vector<Biomes> biomes);
	~BiomeHandler();

	int GetTotalBiomes();
	int GetTotalInstances();
	void GivePreset(int biomeID, size_t index, GameObject* preset);
	GameObject* TakePreset(int biomeID, size_t index);

private:
	std::vector<PresetHandler*> _presetHandlers;
};

#endif // !BIOMEHANDLER_HPP
