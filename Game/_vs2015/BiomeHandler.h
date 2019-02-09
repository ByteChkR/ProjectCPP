#ifndef BIOMEHANDLER_HPP

#define BIOMEHANDLER_HPP

#include "mge/core/GameObject.hpp"
#include <vector>
#include "PresetHandler.hpp"

class BiomeHandler
{
public:
	static BiomeHandler* instance;
	//biomes[i][j] = Single Obstacle;  i = biomeID ; j = obstacleType
	BiomeHandler(std::vector<std::vector<GameObject*>> biomes);
	~BiomeHandler();

	int GetTotalBiomes();
	void GivePreset(int biomeID, size_t index, GameObject* preset);
	GameObject* TakePreset(int biomeID, size_t index);

private:
	std::vector<PresetHandler*> _presetHandlers;
};

#endif // !BIOMEHANDLER_HPP
