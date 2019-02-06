#include "MapBuilder.h"
#include "mge/core/GameObject.hpp"
#include "PresetHandler.hpp"
#include "mge/util/MapGenerator.h"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/World.hpp"
MapBuilder::MapBuilder(float generationOffset, float segmentStep)
{
	_container = new GameObject("CONTAINER");
	genOffset = generationOffset;
	totalTime = 0;
	segStep = segmentStep;

	lanes = MapGenerator::instance->GetNumberOfLanes();

	std::vector<Lane*> lans = MapGenerator::instance->GetAllLanes();
	map = PrepareMap(lans, lans[0]->GetSegments().size());


}

GameObject* MapBuilder::GetContainer()
{
	return _container;
}

void MapBuilder::Update()
{

	float dist;
	for (int i = map.size() - 1; i >= 0; i--)
	{

		if (map[i].second != nullptr && map[i].second->getWorldPosition().z < 0)
		{
			PresetHandler::instance->GivePreset(map[i].first, map[i].second);
			map[i].second = nullptr;
		}
		else
		{
			float dist = (i / lanes) * segStep;
			if (glm::abs(_container->getLocalPosition().z + genOffset) > dist)
			{
				int lane = i % lanes;
				glm::vec3 pos = MapGenerator::instance->GetLaneAt(lane)->GetPosition() + glm::vec3(0, 0, 1) * (i / lanes) / segmentCount * segStep;
				GameObject* obj = new GameObject("");//PresetHandler::instance->TakePreset(map[i].first);
				obj->setParent(_container);
				obj->setLocalPosition(pos);
			}
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
		for (size_t j = 0; j < arrs.size(); j++)
		{
			ret.push_back(std::pair<int, GameObject*>(arrs[j][i], nullptr));
		}
	}
	return ret;
}