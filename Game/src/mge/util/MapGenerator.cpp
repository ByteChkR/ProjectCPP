#include "MapGenerator.h"
#include <fstream>
#include <iostream>
#include "mge/config.hpp"
MapGenerator * MapGenerator::instance = nullptr;
std::default_random_engine MapGenerator::e;

struct Part
{
	std::vector<Lane> lanes;
};

MapGenerator::MapGenerator(std::string pName, bool isInstance)
{
	e = std::default_random_engine(seed);
	  //e = d;
	if(isInstance)instance = this;
	std::vector< Part> parts;
	std::vector<int> steps;
	std::string fullPath = config::MGE_MAP_PATH + pName;

	int randomize = 0;
	int columns = 0;
	int rows = 0;
	int numberOfParts = 0;

	std::cout<<"The path of the file: " << fullPath << '\n';

	std::ifstream file(fullPath);
	file >> randomize;
	file >> columns;
	file >> rows;

	for (int i = 0; i < rows; i++)
	{
		int a;
		file >> a;
		steps.push_back(a);
	}

	file >> numberOfParts;

	for (int i = 0; i < numberOfParts; i++)
	{
		int a;
		file >> a;
		_biomes.push_back(a);
	}

	std::cout <<"columns: "<< columns << " rows: " << rows << " number of parts: " << numberOfParts<<'\n';

	for (int i = 0; i < numberOfParts; i++)
	{
		std::cout <<"reading part " << i << '\n';
		Part part;
		for (int j = 0; j < rows; j++)
		{
			std::cout << "reading lane " << j <<" of part "<< i << '\n';
			Lane  lane(glm::vec3(0,0,0),0,0,0,0,std::vector<int>(),0);
			for (int k = 0; k < columns; k++)
			{
				std::cout << "reading segment " << k << '\n';
				int segment;
				file >> segment;
				lane.AddSegment((int)segment);
			}
			part.lanes.push_back(lane);

		}

		parts.push_back(part);

	}
	std::cout << "reading finished"<< '\n';

	file.close();
	

	// randomize the parts
	if (randomize == 1)
	{
		std::shuffle(parts.begin(), parts.end(), e);
	}

	for (int i = 0; i < rows; i++)
	{
		int laneLeft;
		int laneRight;
		if (i == 0)
		{
			laneLeft = -1;
			laneRight = 1;
		}
		else
		{
			if (i == rows - 1)
			{
				laneLeft = rows - 2;
				laneRight = -1;
			}
			else
			{
				laneLeft = i - 1;
				laneRight = i + 1;
			}
		}



		std::vector<int> sumedSegments = parts[0].lanes[i].GetSegments();

		{
			for (int j = 1; j < (int)parts.size(); j++)
			{
				for (int k = 0; k < columns; k++)
				{
					sumedSegments.push_back(parts[j].lanes[i].GetSegments()[k]);
				}
			}
		}
		

		Lane * lane = new Lane(glm::vec3(0 + _laneSpace * i, 0, 0), laneLeft, laneRight, 0, 0, sumedSegments,steps[i]);
		_lanes.push_back(lane);

	}

	for (int i = 0; i < (int)_lanes.size(); i++)
	{
		std::cout <<"Step of line "<< i<< " is: "<< _lanes[i]->GetStep() << " " << '\n';
		for (int j = 0; j < columns; j++)
		{
			std::cout << _lanes[i]->GetSegments()[j]<<" ";
		}
		std::cout << '\n';
	}

}


MapGenerator::~MapGenerator()
{
	instance = nullptr;

	for (int i = 0; i < (int)_lanes.size(); i++)
	{
		delete _lanes[i];
	}

	_lanes.clear();
}

Lane* MapGenerator::GetLaneAt(size_t pIndex)
{
	if (pIndex > _lanes.size() - 1)
	{
		printf("Lane is out of the range");
	}

	return _lanes[pIndex];
}

std::vector<Lane*> MapGenerator::GetAllLanes()
{
	return _lanes;
}

size_t MapGenerator::GetNumberOfLanes()
{
	return (int)_lanes.size();
}


std::vector<int> MapGenerator::GetBiomes()
{
	return _biomes;
}

int MapGenerator::GetBiomeAt(int pNumber)
{
	if (pNumber > (int)_biomes.size() - 1 || pNumber < 0)
	{
		std::cout << "\n Trying to get a wrong biome \n ";
		return -1;
	}
	return _biomes[pNumber];
}

int MapGenerator::GetPartCount()
{
	return (int)_biomes.size();
}