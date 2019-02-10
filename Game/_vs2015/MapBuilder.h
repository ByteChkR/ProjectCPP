#ifndef MAPBUILDER_HPP
#define MAPBUILDER_HPP
#include <vector>
#include "mge/util/Lane.h"
#include "mge/core/GameObject.hpp"
#include "mge/util/MapGenerator.h"
#include "Level.h"
class MapBuilder
{
public:
	MapBuilder(float generationOffset, float removalOffset);
	~MapBuilder();
	void Update();
	std::vector<std::pair<int, GameObject*>> PrepareMap(std::vector<Lane*> lanes, size_t length);
	GameObject* GetContainer();
	static MapBuilder* instance;
	void UnloadGen(MapGenerator* gen, std::vector<std::pair<int, GameObject*>>* list);
	void ReloadGen(MapGenerator* gen, std::vector<std::pair<int, GameObject*>>* list);
	void Reload();
	void Unload();
private:
	GameObject* _container;
	void UpdateGen(MapGenerator* gen, std::vector<std::pair<int, GameObject*>>* list);

	
	std::vector<std::pair<int, GameObject*>> _mapPropList;
	std::vector<std::pair<int, GameObject*>> _decoPropList;
	float genOffset;
	float remOffset;
};

#endif // !MAPBUILDER_HPP
