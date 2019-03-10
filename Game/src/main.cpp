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


int GetFlag(std::string flag, int argc, char *argv[])
{
	for (int i = 0; i < argc; i++)
	{

		if (argv[i] == flag)return i;

	}
	return -1;
}


int main(int argc, char *argv[])
{


	int engineSettingsID = GetFlag("-e", argc, argv);
	std::string enginePath = config::ENGINE_SETTINGS;
	if (engineSettingsID >= 0 && argc > engineSettingsID + 1 && argv[engineSettingsID + 1][0] != '-')
	{
		enginePath = argv[engineSettingsID + 1];
	}

	new EngineSettings(enginePath);

	bool forcewindowMode = GetFlag("-forceWindow", argc, argv) != -1;

	//int t;
	//std::cin >> t;

	Debug::Log("Starting Game...", WARNINGS_ERRORS_LOG1);
	Debug::Log("with ArgCount: " + std::to_string(argc), WARNINGS_ERRORS_LOG2);


	AbstractGame* game = new MGEDemo(forcewindowMode, argc, argv);

	game->initialize();


	game->run();

	delete game;

	return 0;
}



