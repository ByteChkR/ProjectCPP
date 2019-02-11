#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP
#include <string>
#include <vector>
#include "lua.hpp"
#include "Level.h"

class LevelManager
{
public:
	static LevelManager* instance;
	LevelManager(std::string maplist);
	void ChangeLevel(int index);

private:
	std::vector<std::string> maps;
	Level* currentLevel;
};


#endif // !LEVELMANAGER_HPP
