#include "MapGenerator.h"
#include <fstream>
#include <iostream>
#include <string>
#include "mge/config.hpp"
#include "../_vs2015/Debug.h"

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
	if (isInstance)instance = this;
	std::vector< Part> parts;
	std::vector<int> steps;

	std::string fullPath = _mapsLocation + pName;

	std::ifstream file(fullPath);


	int randomize = 0;
	int columns = 0;
	int rows = 0;
	int numberOfParts = 0;

	Debug::Log("The path of the file: " + fullPath, DebugLevel::WARNINGS_ERRORS_LOG2);

	std::string s;
	file.seekg(0, std::ios::end);
	s.reserve((int)file.tellg());
	file.seekg(0, std::ios::beg);

	s.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

	file.close();

	//file = std::ifstream(fullPath);

	int index = 0;

	//file >> randomize;
	randomize = NextInt(s, index, &index);
	//file >> columns;
	columns = NextInt(s, index, &index);
	//file >> rows;
	rows = NextInt(s, index, &index);


	for (int i = 0; i < rows; i++)
	{
		int a;
		//file >> a;
		a = NextInt(s, index, &index);
		steps.push_back(a);
	}

	//file >> numberOfParts;
	numberOfParts = NextInt(s, index, &index);


	for (int i = 0; i < numberOfParts; i++)
	{
		int a;
		//file >> a;
		a = NextInt(s, index, &index);
		_biomes.push_back(a);
	}

	Debug::Log("columns: " + std::to_string(columns) + " rows: " + std::to_string(rows) + " number of parts: " + std::to_string(numberOfParts), WARNINGS_ERRORS_LOG3);

	for (int i = 0; i < numberOfParts; i++)
	{
		if (numberOfParts < 100)Debug::Log("reading part " + std::to_string(i), ALL);
		else if (numberOfParts >= 1000 && i % 250 == 0)Debug::Log("reading part " + std::to_string(i) + " to " + std::to_string(i + 250), ALL);
		else if (numberOfParts < 1000 && i % 25 == 0)Debug::Log("reading part " + std::to_string(i) + " to " + std::to_string(i + 25), ALL);

		Part part;
		for (int j = 0; j < rows; j++)
		{
			Lane  lane(glm::vec3(0, 0, 0), 0, 0, 0, 0, std::vector<int>(), 0);
			for (int k = 0; k < columns; k++)
			{
				int segment;
				//file >> segment;
				segment = NextInt(s, index, &index);
				lane.AddSegment((int)segment);
			}
			part.lanes.push_back(lane);

		}

		parts.push_back(part);

	}
	Debug::Log("reading map finished", WARNINGS_ERRORS_LOG1);


	//file.close();


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


		Lane * lane = new Lane(glm::vec3(0 + _laneSpace * i, 0, 0), laneLeft, laneRight, 0, 0, sumedSegments, steps[i]);
		_lanes.push_back(lane);

	}


}

int MapGenerator::NextInt(std::string file, int index, int* newIndex)
{
	int startWord = -1;
	int endWord = -1;
	for (size_t i = index; i < file.size(); i++)
	{
		if (startWord == -1)
		{
			if (file[i] <= NINE_ID && file[i] >= ZERO_ID)
			{
				startWord = i;
			}
		}
		else if (startWord != -1 && endWord == -1)
		{
			if (file[i] > NINE_ID || file[i] < ZERO_ID)
			{
				endWord = i;
				break;
			}
		}
	}
	*newIndex = file.size() - 1;
	if (endWord == -1 || startWord == -1) return 0;

	*newIndex = endWord;

	return std::stoi(file.substr(startWord, endWord - startWord));
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
		Debug::LogError("Lane is out of range");
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
		Debug::LogError("Trying to get a wrong biome");

		return -1;
	}
	return _biomes[pNumber];
}

size_t MapGenerator::GetPartCount()
{
	return _biomes.size();
}