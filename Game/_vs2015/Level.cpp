#include "Level.h"
#include <string>
#include "mge/util/MapGenerator.h"

Level* Level::instance = nullptr;

Level::Level(std::string map, std::string decoration)
{
	instance = this;
	_map = new MapGenerator(map);
	_decoration = new MapGenerator(decoration, false);
}
Level::~Level()
{
	_map = nullptr;
	_decoration = nullptr;
}
MapGenerator* Level::GetDeco()
{
	return _decoration;
}

MapGenerator* Level::GetMap()
{
	return _map;
}