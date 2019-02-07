#include "MapBuilder.h"
#include "mge/core/GameObject.hpp"
#include "PresetHandler.hpp"
#include "mge/util/MapGenerator.h"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/World.hpp"
MapBuilder* MapBuilder::instance = nullptr;

MapBuilder::MapBuilder(float generationOffset, float segmentStep)
{
	instance = this;
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		
		_container->setLocalPosition(_container->getLocalPosition() + glm::vec3(0, 0, 1)*0.4f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {

		_container->setLocalPosition(_container->getLocalPosition() - glm::vec3(0, 0, 1)*0.4f);
	}

	float dist;
	for (int i = map.size()-1; i >= 0; i--)
	{
		glm::vec3 v, c;
		if (map[i].second != nullptr && ((v=(map[i].second->getLocalPosition()+_container->getLocalPosition())).z > 1 || v.z < -genOffset) )
		{
			PresetHandler::instance->GivePreset(map[i].first, map[i].second);
			map[i].second = nullptr;
  			//std::cout << "Erased";
			//std::cout << map.size()<<"\n";
		}
		else if(map[i].second == nullptr)
		{
			float dist = (i / lanes) * segStep;
			float reldist = dist - _container->getLocalPosition().z;
			if (reldist > 0 && genOffset >= reldist)
			{
				//std::cout << "Created\n";
				int lane = i % lanes;
				glm::vec3 pos = MapGenerator::instance->GetLaneAt(lane)->GetPosition() + glm::vec3(0, 0, -1) * dist;
				GameObject* obj = PresetHandler::instance->TakePreset(map[i].first);
				map[i].second = obj;
				if (obj->getParent() != _container)
					_container->add(obj);
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
			//glm::vec3 pos = MapGenerator::instance->GetLaneAt(j)->GetPosition() + glm::vec3(0, 0, -1) * i * segStep;
			////std::cout << pos.x << " " << pos.y << " " << pos.z << '\n';
			//GameObject* obj = PresetHandler::instance->TakePreset(arrs[j][i]);
			//obj->setParent(_container);
			//obj->setLocalPosition(pos);
			ret.push_back(std::pair<int, GameObject*>(arrs[j][i], nullptr));
		}
	}
	return ret;
}