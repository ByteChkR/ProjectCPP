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

	std::cout<<"The path of the file: " << fullPath << '\n';

	std::ifstream file(fullPath);
	file >> columns;
	file >> rows;
	file >> numberOfParts;
	std::cout <<"columns: "<< columns << " rows: " << rows << " number of parts: " << numberOfParts<<'\n';

	for (int i = 0; i < numberOfParts; i++)
	{
		std::cout <<"reading part " << i << '\n';
		Part part;
		for (int j = 0; j < rows; j++)
		{
			std::cout << "reading lane " << j <<" of part "<< i << '\n';
			Lane  lane(glm::vec3(0,0,0),0,0,0,0,std::vector<int>());
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
			if (i == (int)parts.size() - 1)
			{
				laneLeft = (int)parts.size() - 2;
				laneRight = -1;
			}
			else
			{
				laneLeft = i - 1;
				laneRight = i + 1;
			}
		}

		//TODO: randomize the parts


		std::vector<int> sumedSegments = parts[0].lanes[i].GetSegments();

		{
			for (int j = 1; j < (int)parts.size(); j++)
			{
				for (int k = 0; k < columns; k++)
				{
					sumedSegments.push_back(parts[j].lanes[i].GetSegments()[k]);
				}
				//sumedSegments.insert(sumedSegments.end(), parts[j].lanes[i].GetSegments().begin(),parts[j].lanes[i].GetSegments().end());
			}
		}

		Lane * lane = new Lane(glm::vec3(0 + _laneSpace * i, 0, 0), laneLeft, laneRight, 0, 0, sumedSegments);
		_lanes.push_back(lane);

	}

	for (int i = 0; i < (int)_lanes.size(); i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << _lanes[i]->GetSegments()[j]<<" ";
		}
		std::cout << '\n';
	}

}


MapGenerator::~MapGenerator()
{
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
