#include "mge/util/BiomeHandler.h"
#include "mge/util/Biome.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>


BiomeHandler* BiomeHandler::instance = nullptr;

BiomeHandler::BiomeHandler(std::vector<Biome*> biomes)
{
	instance = this;
	_biomes = biomes;


}

BiomeHandler::~BiomeHandler()
{

}

int BiomeHandler::GetTotalBiomes() 
{
	return _biomes.size();
}
int BiomeHandler::GetTotalInstances()
{
	int ret = 0;
	for each (Biome* b in _biomes)
	{
		ret+=b->GetTotalInstances();
	}
	return ret;
}

int BiomeHandler::GetTotalActiveInstances()
{
	int ret = 0;
	for each (Biome* b in _biomes)
	{
		ret += b->GetTotalActiveInstances();
	}
	return ret;
}

void BiomeHandler::UnloadBiome(int id)
{
	if (id < 0 || id > _biomes.size())return;
	if (_biomes[id]->GetTotalActiveInstances() != 0)return;
	_biomes[id]->Unload();
}

void BiomeHandler::GivePreset(size_t biomeID, size_t index, GameObject* preset) 
{
	if (biomeID >= _biomes.size())return;
	return _biomes[biomeID]->GivePreset(index, preset);
}

GameObject* BiomeHandler::TakePreset(size_t biomeID, size_t index) 
{
	if (biomeID >= _biomes.size())return nullptr;
	return _biomes[biomeID]->TakePreset(index);
}