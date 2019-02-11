#include "MapBuilder.h"
#include "mge/core/GameObject.hpp"
#include "PresetHandler.hpp"
#include "mge/util/BiomeHandler.h"
#include "mge/util/MapGenerator.h"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/World.hpp"
#include "Level.h"
MapBuilder* MapBuilder::instance = nullptr;

MapBuilder::MapBuilder(float generationOffset, float removalOffset)
{
	instance = this;
	_container = new GameObject("CONTAINER");
	genOffset = generationOffset;
	remOffset = removalOffset;
	/*_map = Level::instance->GetMap();
	_deco = Level::instance->GetDeco();*/


	if (Level::instance == nullptr) return;
	std::vector<Lane*> lans = Level::instance->GetMap()->GetAllLanes();
	_mapPropList = PrepareMap(lans, lans[0]->GetSegments().size());
	if (Level::instance->GetDeco() != nullptr)
	{
		lans = Level::instance->GetDeco()->GetAllLanes();
		_decoPropList = PrepareMap(lans, lans[0]->GetSegments().size());
	}
}

void MapBuilder::Reload()
{
	ReloadGen(Level::instance->GetMap(), &_mapPropList);
	ReloadGen(Level::instance->GetDeco(), &_decoPropList);
}

void MapBuilder::Unload()
{
	if (&_mapPropList != nullptr && _mapPropList.size() > 0)
		UnloadGen(Level::instance->GetMap(), &_mapPropList);
	if (&_decoPropList != nullptr && _decoPropList.size() > 0)
		UnloadGen(Level::instance->GetDeco(), &_decoPropList);

}

void MapBuilder::UnloadGen(MapGenerator* gen, std::vector<std::pair<int, GameObject*>>* list)
{
	if (gen == nullptr) return;
	for (size_t i = 0; i < (*list).size(); i++)
	{
		int biomeID = i / gen->GetNumberOfLanes() / gen->GetPartCount();

		BiomeHandler::instance->GivePreset(gen->GetBiomeAt(biomeID), (*list)[i].first, (*list)[i].second);
		(*list)[i].second = nullptr;
	}
	list->clear();
}

void MapBuilder::ReloadGen(MapGenerator* gen, std::vector<std::pair<int, GameObject*>>* list)
{
	if (gen == nullptr) return;
	UnloadGen(gen, list);

	std::vector<Lane*> lans = gen->GetAllLanes();
	*list = PrepareMap(lans, lans[0]->GetSegments().size());
}

MapBuilder::~MapBuilder()
{
	instance = nullptr;
	delete _container;
}

GameObject* MapBuilder::GetContainer()
{
	return _container;
}

void MapBuilder::UpdateGen(MapGenerator* gen, std::vector<std::pair<int, GameObject*>>* list)
{
	if (gen == nullptr || gen->GetNumberOfLanes() == 0 || gen->GetPartCount() == 0) return;
	int lastAdd = -1;
	for (int i = 0; i < list->size(); ++i)
	{
		glm::vec3 v;
		
		if ((*list)[i].second != nullptr && ((v = ((*list)[i].second->getLocalPosition() + _container->getLocalPosition())).z > remOffset || v.z < -genOffset))
		{
			int biomeID = (i / gen->GetNumberOfLanes() / (float)gen->GetLaneAt(0)->GetSegments().size())*gen->GetPartCount();

			BiomeHandler::instance->GivePreset(gen->GetBiomeAt(biomeID), (*list)[i].first, (*list)[i].second);
			(*list)[i].second = nullptr;
		}
		else if ((*list)[i].second == nullptr)
		{
			if (lastAdd != -1 && lastAdd != i - 1)break;
			int lane = i % gen->GetNumberOfLanes();
			int biomeID = i / gen->GetNumberOfLanes();
			float dist = biomeID * gen->GetLaneAt(lane)->GetStep();
			float reldist = dist - _container->getLocalPosition().z;
			if (reldist > remOffset && genOffset >= reldist)
			{
				lastAdd = i;
				biomeID = (biomeID / (float)gen->GetLaneAt(0)->GetSegments().size())*gen->GetPartCount();
				//std::cout << "Created\n";
				glm::vec3 pos = gen->GetLaneAt(lane)->GetPosition() + glm::vec3(0, 0, -1) * dist;
				GameObject* obj = BiomeHandler::instance->TakePreset(gen->GetBiomeAt(biomeID), (*list)[i].first);
				(*list)[i].second = obj;
				if (obj->getParent() != _container)
					_container->add(obj);
				obj->setLocalPosition(pos);
			}
		}
	}
}

void MapBuilder::Update(float pTime)
{
	if (Level::instance == nullptr) return;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {

		_container->setLocalPosition(_container->getLocalPosition() - glm::vec3(0, 0, 30) * pTime);
	}
	else
		_container->setLocalPosition(_container->getLocalPosition() + glm::vec3(0, 0, 30)* pTime);

	UpdateGen(Level::instance->GetMap(), &_mapPropList);
	UpdateGen(Level::instance->GetDeco(), &_decoPropList);

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
			ret.push_back(std::pair<int, GameObject*>(arrs[j][i], nullptr));
		}
	}
	return ret;
}