#ifndef ScoreManager_HPP

#define ScoreManager_HPP

#include "mge/util/DataManager.h"
#include "mge/core/GameObject.hpp"
#include <vector>

class GameObject;

class ScoreManager
{
public:

	static struct Score
	{
		float value;
		std::string name;

		Score(float pValoue, std::string pName)
		{
			value = pValoue;
			name = pName;
		}

	};

	

	static ScoreManager * instance;
	ScoreManager();
	~ScoreManager();

	std::vector<Score> GetScores();
	void AddScore(float pValue, std::string pName);



private:
	struct LessThenValue
	{
		inline bool operator() (const Score& pStruct1, const Score & pStruct2)
		{
			return(pStruct1.value < pStruct2.value);
		}
	};

};

#endif // !DataManager_HPP
