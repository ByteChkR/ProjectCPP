#ifndef BIOMEHANDLER_HPP

#define BIOMEHANDLER_HPP

#include "mge/core/GameObject.hpp"
#include <vector>
#include "../_vs2015/PresetHandler.hpp"
#include "mge/util/Biome.h"

class BiomeHandler
{
public:
	static BiomeHandler* instance;
	//biomes[i][j] = Single Obstacle;  i = biomeID ; j = obstacleType
	BiomeHandler(std::vector<Biome*> biomes);
	~BiomeHandler();

	void UnloadBiome(int id);
	int GetTotalBiomes();
	int GetTotalInstances();
	int GetTotalActiveInstances();
	void GivePreset(size_t biomeID, size_t index, GameObject* preset);
	GameObject* TakePreset(size_t biomeID, size_t index);

private:
	std::vector<Biome*> _biomes;
};

#endif // !BIOMEHANDLER_HPP
