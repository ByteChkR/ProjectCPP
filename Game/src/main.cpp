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
#include "../_vs2015/StoryPanelHandler.h"
#include "mge/util/DataManager.h"
#include "../_vs2015/Debug.h"
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
	
	//int t;
	//std::cin >> t;

	Debug::Log("Starting Game...", WARNINGS_ERRORS_LOG1);
	Debug::Log("with ArgCount: " + std::to_string(argc), WARNINGS_ERRORS_LOG2);

	bool wMode = false;
	if (argc > 1)wMode = argv[1][0] == 'w';

	AbstractGame* game = new MGEDemo(argc, argv, wMode);

	game->initialize();


	game->run();

	delete game;

	return 0;
}



