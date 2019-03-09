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
	void NextLevel();
	void ReloadLevel();
	int GetCurrent();
	void AddGroundTexture(std::string pFileLocation);
	void AddBackgroundTexture(std::string pFileLocation);

private:
	std::vector<std::string> _maps;
	Level* _currentLevel = nullptr;
	std::vector<std::string> _groundTextures;
	std::vector<std::string> _backgroundTextures;
	int _curLevel;
};


#endif // !LEVELMANAGER_HPP
