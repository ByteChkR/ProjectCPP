#include "MapBuilder.h"
#include "mge/core/GameObject.hpp"
#include "PresetHandler.hpp"
#include "mge/util/BiomeHandler.h"
#include "mge/util/MapGenerator.h"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/World.hpp"
#include "Level.h"
#include "StaticBoxCollider.hpp"
MapBuilder* MapBuilder::instance = nullptr;

MapBuilder::MapBuilder(float generationOffset, float removalOffset)
{
	instance = this;
	lastRemove = 0;
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
	lastRemove = 0;
	for (size_t i = 0; i < (*list).size(); i++)
	{
		if ((*list)[i].second == nullptr)continue;
		int biomeID = i / gen->GetNumberOfLanes() / gen->GetPartCount();

		BiomeHandler::instance->GivePreset(gen->GetBiomeAt(biomeID), (*list)[i].first, (*list)[i].second);
		(*list)[i].second = nullptr;
	}
	list->clear();
}

void MapBuilder::AddToPropList(std::vector<std::pair<int, GameObject*>> * list, MapGenerator* gen, size_t index)
{
	int lane = index % gen->GetNumberOfLanes();
	int biomeID = index / gen->GetNumberOfLanes(); //theoretical distance from container origin
	float dist = biomeID * gen->GetLaneAt(lane)->GetStep(); //Distance from container origin with step size
	float reldist = dist - _container->getLocalPosition().z; //Global distance to origin

	//std::cout << "Reldist: " << std::to_string(reldist) << '\n';
	if (reldist > -remOffset && reldist < genOffset)
	{
		biomeID = (biomeID / (float)gen->GetLaneAt(0)->GetSegments().size())*gen->GetPartCount();
		//std::cout << "Created\n";
		glm::vec3 pos = gen->GetLaneAt(lane)->GetPosition() + glm::vec3(0, 0, -1) * dist;
		//std::cout << "Offset On Lane: " << dist << '\n';
		GameObject* obj = BiomeHandler::instance->TakePreset(gen->GetBiomeAt(biomeID), (*list)[index].first);
		(*list)[index].second = obj;
		(*list)[index].second->EnableBehaviours();
		if (obj->getParent() != _container)
			_container->add(obj);
		obj->setLocalPosition(pos);
	}
}
void MapBuilder::RemoveFromPropList(std::vector<std::pair<int, GameObject*>> * list, MapGenerator* gen, size_t index)
{
	int biomeID = (index / gen->GetNumberOfLanes() / (float)gen->GetLaneAt(0)->GetSegments().size())*gen->GetPartCount();
	(*list)[index].second->DisableBehaviours();
	BiomeHandler::instance->GivePreset(gen->GetBiomeAt(biomeID), (*list)[index].first, (*list)[index].second);
	(*list)[index].second = nullptr;
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

	//float delta = _container->getLocalPosition().z - lastContainerPos;


	int end = lastRemove + gen->GetNumberOfLanes()*genOffset;
	end = glm::min(end, (int)list->size() - 1);

	//float fstart = ((int)_container->getLocalPosition().z - remOffset)*gen->GetNumberOfLanes();
	//int start = (int)(glm::max(fstart, 0.0f));

	//std::cout << "I size: " << std::to_string(end-lastRemove) << '\n';

	for (size_t i = lastRemove; i < end; ++i)
	{
		if ((*list)[i].second != nullptr)
		{
			glm::vec3 v = ((*list)[i].second->getLocalPosition() + _container->getLocalPosition());

			if (v.z > remOffset)
			{
				RemoveFromPropList(list, gen, i);
				lastRemove = i;
			}
			else if (v.z < -genOffset)
			{
				RemoveFromPropList(list, gen, i);
			}
		}
		else if ((*list)[i].second == nullptr)
		{

			//if (lastAdd != -1 && lastAdd < i - 1)break;
			AddToPropList(list, gen, i);
			lastAdd = i;

		}
	}
}

void MapBuilder::Update(float pTime)
{
	if (Level::instance == nullptr) return;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {

		_container->setLocalPosition(_container->getLocalPosition() - glm::vec3(0, 0, 20) * pTime);
	}
	else
		_container->setLocalPosition(_container->getLocalPosition() + glm::vec3(0, 0, 20)* pTime);

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