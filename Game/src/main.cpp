#include <iostream>

#include "mge/core/AbstractGame.hpp"
#include "mge/MGEDemo.hpp"
#include "mge\util\AudioManager.h"
#include "mge\util\MapGenerator.h"
#include "../_vs2015/Level.h"
#include "../_vs2015/LevelManager.h"
#include <vector>
#include "mge/config.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "../_vs2015/GameStateManager.h"
#include "mge/util/DataManager.h"
/**
 * Main entry point for the Micro Engine.

 * Design goals:
 * - correct division of OpenGL into appropriate wrapper classes
 * - simple design
 * - each class should know as little as possible about other classes and non related parts of OpenGL
 * - the engine must allow different objects with different transforms, meshes, materials (shaders) etc
 * - consistent coding conventions
 * - reusable and extendable core set of classes which should require no modification
 *   (in other words it is possible to have a working "empty" example)
 *
 * All documentation is contained within the HEADER files, not the CPP files if possible.
 *
 */
int main(int argc, char *argv[])
{
	std::string filename = "maplist.lua";
	LevelManager* lm = nullptr;
	bool isRaw;
	std::string test = argv[0];
	if (argc == 2)
	{
		isRaw = false;
		
		filename = argv[1];
	}
	else if (argc > 2)
	{
		filename = argv[1];
		isRaw = argv[2][0] == 'r';
	}
	else
	{
		lm = new LevelManager(filename);
	}
	AudioManager * audioManager = new AudioManager();
	GameStateManager * gameStateManager = new GameStateManager();
	DataManager * dataManager = new DataManager();
	//int t;
	//std::cin >> t;

	std::cout << "Starting Game" << std::endl;

	AbstractGame* game = new MGEDemo();

	game->initialize();

	if(lm != nullptr)lm->ChangeLevel(0);
	else Level* level = isRaw?new Level(true, filename):new Level(config::MGE_MAP_PATH+filename);

	game->run();

	delete game;

	return 0;
}



