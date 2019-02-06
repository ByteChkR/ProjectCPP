#include "MapGenerator.h"
#include <fstream>
#include <iostream>

MapGenerator * MapGenerator::instance;

struct Part
{
	std::vector<Lane> lanes;
};

MapGenerator::MapGenerator(std::string pName)
{
	instance = this;
	std::vector< Part> parts;

	std::string fullPath = _filePath + pName;

	int columns = 0;
	int rows = 0;
	int numberOfParts = 0;

	std::ifstream file(fullPath);
	file >> columns;
	file >> rows;
	file >> numberOfParts;
	std::cout << columns << rows << numberOfParts;

	for (int i = 0; i < numberOfParts; i++)
	{
		Part part;
		for (int j = 0; j < rows; j++)
		{
			
		}

	}





	file.close();


}


MapGenerator::~MapGenerator()
{
}

Lane* MapGenerator::GetLaneAt(int pIndex)
{
	if (pIndex > _lanes.size() - 1)
	{
		printf("Lane is out of the range");
	}

	return _lanes[pIndex];
}
