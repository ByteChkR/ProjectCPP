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
	void Update(float pTime);
	std::vector<std::pair<int, GameObject*>> PrepareMap(std::vector<Lane*> lanes, size_t length);
	GameObject* GetContainer();
	static MapBuilder* instance;
	void UnloadGen(MapGenerator* gen, std::vector<std::pair<int, GameObject*>>* list);
	void ReloadGen(MapGenerator* gen, std::vector<std::pair<int, GameObject*>>* list);
	void Reload();
	void Unload();
	float GetProgress();

	float genOffset;
private:
	GameObject* _container;
	void UpdateGen(MapGenerator* gen, std::vector<std::pair<int, GameObject*>>* list);
	

	void RemoveFromPropList(std::vector<std::pair<int, GameObject*>> *list, MapGenerator* gen, size_t index);
	void AddToPropList(std::vector<std::pair<int, GameObject*>> *list, MapGenerator* gen, size_t index);
	std::vector<std::pair<int, GameObject*>> _mapPropList;
	std::vector<std::pair<int, GameObject*>> _decoPropList;
	float remOffset;
	int lastRemove;
};

#endif // !MAPBUILDER_HPP
