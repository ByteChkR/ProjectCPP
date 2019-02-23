#include "mge/util/ScoreManager.h"
#include <fstream>
#include <iostream>

 ScoreManager * ScoreManager::instance;

ScoreManager:: ScoreManager()
{
	instance = this;
}
ScoreManager::~ScoreManager()
{
	instance = nullptr;
}

std::vector<ScoreManager::Score> ScoreManager::GetScores()
{
	std::vector<Score> scores;

	std::ifstream file("mge/scoreboard.txt");

	while (true)
	{
		if (file.eof())
		{
			break;
		}

		float value;
		std::string name;
		file >> value;
		file >> name;

		std::cout << value << "  " << name<< "\n";

		Score score(value, name);
		scores.push_back(score);
	}

	return scores;

}
void  ScoreManager::AddScore(float pValue, std::string pName)
{
	Score addedScore(pValue, pName);

	std::vector<Score> scores = GetScores();


}




