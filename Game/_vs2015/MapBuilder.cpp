#include "MapBuilder.h"
#include "mge/core/GameObject.hpp"
#include "PresetHandler.hpp"
MapBuilder::MapBuilder(float generationOffset, float segmentStep)
{
	genOffset = generationOffset;
	segStep = segmentStep;
}


void MapBuilder::Update(float pTime)
{

}

void MapBuilder::PrepareMap(std::vector<Lane*> lanes, int length)
{
	std::vector<std::vector<int>> arrs = std::vector<std::vector<int>>();
	for (int i = 0; i < lanes.size(); i++)
	{
		arrs.push_back(lanes[i]->GetSegments());
	}

	GameObject* part = new GameObject();

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; i < arrs.size(); i++)
		{
			GameObject* preset = PresetHandler::instance->TakePreset(arrs[j][i]);
			glm::vec3 offset = lanes[j]->GetPosition() + (length * segStep)*glm::vec3(0,0,-1);
			preset->setLocalPosition(offset);
			part->add(preset);
		}
	}
}