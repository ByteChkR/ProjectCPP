#include <iostream>

#include "mge/core/AbstractGame.hpp"
#include "mge/MGEDemo.hpp"
#include "mge\util\AudioManager.h"
#include "mge\util\MapGenerator.h"
#include "../_vs2015/Level.h"
#include "../_vs2015/LevelManager.h"
#include <vector>
#include "mge/config.hpp"

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
	
	if (argc > 0)
	{
		//filename = argv[1];
		Level* level = new Level(config::MGE_MAP_PATH+ "map1.lua");
	}
	else
	{
		LevelManager* lm = new LevelManager(filename);
	}
	AudioManager * audioManager = new AudioManager();
	
	//int t;
	//std::cin >> t;

    std::cout << "Starting Game" << std::endl;

    AbstractGame* game = new MGEDemo();
    game->initialize();
    game->run();

	delete game;

    return 0;
}



