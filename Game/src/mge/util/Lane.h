#ifndef LANE_H
#define LANE_H
#include <SFML\Graphics.hpp>
#include <vector>
#include "glm.hpp"

class Lane
{
public:

	Lane(glm::vec3 pPosition, int pLeftNeighbour, int pRightNeighbour,float pStartTime,float pEndTime,std::vector<int> pSegments);

	~Lane();
	int GetLeft();
	int GetRight();
	glm::vec3 GetPosition();
	float GetStartTime();
	float GetEndTine();
	std::vector<int> GetSegments();

	//void SetPosition(sf::Vector3f);
	//void SetRightNeighbour(int pNumber);
	//void SetLeftNeighbour(int pNumber);
	//void SetStartTime(float pTime);
	//void SetFinishTime(float pTime);
	
private:


	std::vector<int> _segments;
	glm::vec3 _position;
	int _leftNeighbour;
	int _rightNeighbour;
	float _startTime;
	float _endTime;

};
#endif

