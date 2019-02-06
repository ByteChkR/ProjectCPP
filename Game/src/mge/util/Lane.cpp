#include "Lane.h"
#include "glm.hpp"




Lane::Lane(glm::vec3 pPosition, int pLeftNeighbour, int pRightNeighbour, float pStartTime, float pEndTime, std::vector<int> pSegments)
{
	_segments = pSegments;
	_position = pPosition;
	_leftNeighbour = pLeftNeighbour;
	_rightNeighbour = pRightNeighbour;
	_startTime = pStartTime;
	_endTime = pEndTime;
}


Lane::~Lane()
{
}

int Lane::GetLeft()
{
	return _leftNeighbour;
}
int Lane::GetRight()
{
	return _rightNeighbour;
}

glm::vec3 Lane::GetPosition()
{
	return _position;
}
float Lane::GetStartTime()
{
	return _startTime;
}

float Lane::GetEndTine()
{
	return _endTime;
}

std::vector<int> Lane::GetSegments()
{
	return _segments;
}

