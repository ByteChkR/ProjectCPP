#include "MapBuilder.h"
#include "mge/core/GameObject.hpp"
#include "PresetHandler.hpp"
#include "mge/util/MapGenerator.h"
MapBuilder::MapBuilder(float generationOffset, float segmentStep)
{
	genOffset = generationOffset;
	totalTime = 0;
	segStep = segmentStep;
	map = std::vector<std::pair<int, GameObject*>>();
	std::vector<Lane*> lanes = std::vector<Lane*>();
	for (size_t i = 0; i < MapGenerator::instance->GetLaneCount(); i++)
	{
		lanes.push_back(MapGenerator::instance->GetLaneAt(i));
	}
	map = PrepareMap(lanes, lanes[0]->GetSegments().size());
	

}


void MapBuilder::Update(float pTime)
{
	//totalTime += pTime;

	for (int i = map.size(); i >= 0; i--)
	{
		if (map[i].second != nullptr && map[i].second->getWorldPosition().z < 0)
		{
			PresetHandler::instance->GivePreset(map[i].first, map[i].second);
			map[i].second = nullptr;
		}
		else
		{
			int lane = i % lanes;
			glm::vec3 pos = MapGenerator::instance->GetLaneAt(lane)->GetPosition() + glm::vec3(0,0,1) * (i / lanes) / segmentCount * segStep;
			GameObject* obj = PresetHandler::instance->TakePreset(map[i].first);
			obj->setParent(_container);
			obj->setLocalPosition(pos);
		}
	}
}

std::vector<std::pair<int, GameObject*>> MapBuilder::PrepareMap(std::vector<Lane*> lanes, size_t length)
{
	std::vector<std::vector<int>> arrs = std::vector<std::vector<int>>();
	for (size_t i = 0; i < lanes.size(); i++)
	{
		arrs.push_back(lanes[i]->GetSegments());
	}

	std::vector<std::pair<int, GameObject*>> ret = std::vector<std::pair<int, GameObject*>>();

	for (size_t i = 0; i < length; i++)
	{
		for (size_t j = 0; i < arrs.size(); i++)
		{
			ret.push_back(std::pair<int, GameObject*>(arrs[j][i], nullptr));
		}
	}
	return ret;
}