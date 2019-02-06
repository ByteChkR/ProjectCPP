#ifndef LANE_H
#define LANE_H
#include <SFML\Graphics.hpp>
#include <vector>

class Lane
{
public:
	Lane(sf::Vector3f pPosition, int pLeftNeighbour, int pRightNeighbour,float pStartTime,float pEndTime,std::vector<int> pSegments);
	~Lane();
	int GetLeft();
	int GetRight();
	sf::Vector3f GetPosition();
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
	sf::Vector3f _position;
	int _leftNeighbour;
	int _rightNeighbour;
	float _startTime;
	float _endTime;

};
#endif

