#include "mge/util/ScoreManager.h"
#include <fstream>
#include <algorithm>
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

		float value;
		std::string name;
		file >> value;
		file >> name;

		//std::cout << value << "  " << name<< "\n";

		Score score(value, name);
		scores.push_back(score);
		if (file.eof())
		{
			break;
		}
	}

	file.close();
	scores.pop_back();

	return scores;

}
void  ScoreManager::AddScore(float pValue, std::string pName)
{
	Score addedScore(pValue, pName);

	std::vector<Score> scores = GetScores();
	scores.push_back(addedScore);
	
	int i, j, flag = 1;
	Score temp(0,"");
	int numLength = (int)scores.size();
	for (i = 1; (i <= numLength) && flag; i++)
	{
		flag = 0;
		for (j = 0; j < (numLength - 1); j++)
		{
			if (scores[j + 1].value > scores[j].value)
			{
				temp.value = scores[j].value;
				temp.name = scores[j].name;
				scores[j].name = scores[j + 1].name;
				scores[j].value = scores[j + 1].value;

				scores[j + 1].name = temp.name;
				scores[j + 1].value = temp.value;
				flag = 1;
			}
		}
	}

	while ((int)scores.size() > 10)
	{
		scores.pop_back();
	}

	std::ofstream ofs("mge/scoreboard.txt", std::ofstream::trunc);

	for (int i = 0; i < (int)scores.size(); i++)
	{
		ofs << scores[i].value << " " << scores[i].name << "\n";
	}

	ofs.close();

}




