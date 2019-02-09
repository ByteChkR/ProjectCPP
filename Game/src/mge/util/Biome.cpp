#include "mge/util/Biome.h"

#include <fstream>
#include <iostream>


Biome::Biome(std::string pLuaFile)
{
	_handler = new PresetHandler(std::vector<GameObject*>());
}

Biome::~Biome()
{

}

int Biome::GetTotalInstances()
{
	return _handler->GetTotalInstances();
}

GameObject* Biome::TakePreset(size_t index)
{
	return _handler->TakePreset(index);
}

void Biome::GivePreset(size_t index, GameObject* obj)
{
	_handler->GivePreset(index, obj);
}