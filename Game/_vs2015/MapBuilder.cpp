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
	for (int i = 0; i < map.size(); i++)
	{
		glm::vec3 v;
		if (map[i].second != nullptr && (v=map[i].second->getWorldPosition()).z < 0)
		{
			PresetHandler::instance->GivePreset(map[i].first, map[i].second);
			map[i].second = nullptr;
		}
		else
		{
			float dist = (i / lanes) * segStep;
			if (genOffset > dist)
			{
				int lane = i % lanes;
				glm::vec3 pos = MapGenerator::instance->GetLaneAt(lane)->GetPosition() + glm::vec3(0, 0, -1) * (i % lanes) * segStep;
				GameObject* obj = PresetHandler::instance->TakePreset(map[i].first);
				map[i].second = obj;
				obj->setParent(_container);
				obj->setLocalPosition(pos);
			}
		}
	}
}

std::vector<std::pair<int, GameObject*>> MapBuilder::PrepareMap(std::vector<Lane*> lans, size_t length)
{
	std::vector<std::vector<int>> arrs = std::vector<std::vector<int>>();
	for (size_t i = 0; i < lans.size(); i++)
	{
		arrs.push_back(lans[i]->GetSegments());
	}

	std::vector<std::pair<int, GameObject*>> ret = std::vector<std::pair<int, GameObject*>>();

	for (size_t i = 0; i < length; i++)
	{
		for (size_t j = 0; j < arrs.size(); j++)
		{
			glm::vec3 pos = MapGenerator::instance->GetLaneAt(j)->GetPosition() + glm::vec3(0, 0, -1) * i * segStep;
			//std::cout << pos.x << " " << pos.y << " " << pos.z << '\n';
			GameObject* obj = PresetHandler::instance->TakePreset(arrs[j][i]);
			obj->setParent(_container);
			obj->setLocalPosition(pos);
			ret.push_back(std::pair<int, GameObject*>(arrs[j][i], obj));
		}
	}
	return ret;
}