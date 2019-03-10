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
#include "../_vs2015/PlayerController.hpp"
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

void OverrideEngineSettings(int argc, char *argv[])
{

#pragma region Resolution Override


	int resFlagID;
	if ((resFlagID = GetFlag("-res", argc, argv)) != -1 && argc > resFlagID + 2 && argv[resFlagID + 1][0] != '-' && argv[resFlagID + 2][0] != '-')
	{

		try
		{
			int width = std::stoi(argv[resFlagID + 1]);
			int height = std::stoi(argv[resFlagID + 2]);
			EngineSettings::settings->SetWidth(width);
			EngineSettings::settings->SetHeight(height);
			Debug::Log("Override Resolution: " + std::to_string(width) + " x " + std::to_string(height), ALL);
		}
		catch (std::exception* e)
		{
			Debug::Log("Invalid resolution in -res flag. Skipping.", WARNINGS_ERRORS_ONLY);
		}
	}
#pragma endregion

#pragma region VSync Override

	int vsyncArgID;
	if ((vsyncArgID = GetFlag("-vsync", argc, argv)) != -1 && argc > vsyncArgID + 1 && argv[vsyncArgID + 1][0] != '-')
	{
		try
		{
			int vsyncenabled = std::stoi(argv[vsyncArgID + 1]);
			EngineSettings::settings->SetVSync(vsyncenabled != 0);
			Debug::Log("VSync Override: " + std::to_string(vsyncenabled), ALL);
		}
		catch (std::exception* e)
		{
			Debug::Log("Invalid -vsync flag. Skipping.", WARNINGS_ERRORS_ONLY);
		}
	}


#pragma endregion

#pragma region FPSTarget Override

	int fpsTargetID;
	if ((fpsTargetID = GetFlag("-fpsTarget", argc, argv)) != -1 && argc > fpsTargetID + 1 && argv[fpsTargetID + 1][0] != '-')
	{
		try
		{
			int fpstarget = std::stoi(argv[fpsTargetID + 1]);
			EngineSettings::settings->SetFPSTarget(fpstarget);
			Debug::Log("FPSTarget Override: " + std::to_string(fpstarget), ALL);
		}
		catch (std::exception* e)
		{
			Debug::Log("Invalid -fpsTarget flag. Skipping.", WARNINGS_ERRORS_ONLY);
		}
	}

#pragma endregion

#pragma region WindowMode Override
	int windowModeID;
	if ((windowModeID = GetFlag("-windowMode", argc, argv)) != -1 && argc > windowModeID + 1 && argv[windowModeID + 1][0] != '-')
	{
		try
		{
			int windowMode = std::stoi(argv[windowModeID + 1]);
			EngineSettings::settings->SetWindowMode(windowMode != 0);
			Debug::Log("WindowMode Override: " + std::to_string(windowMode), ALL);
		}
		catch (std::exception* e)
		{
			Debug::Log("Invalid -windowMode flag. Skipping.", WARNINGS_ERRORS_ONLY);
		}
	}
#pragma endregion

#pragma region MSAASamples Override
	int msaaSamplesID;
	if ((msaaSamplesID = GetFlag("-msaa", argc, argv)) != -1 && argc > msaaSamplesID + 1 && argv[msaaSamplesID + 1][0] != '-')
	{
		try
		{
			int msaaSamples = std::stoi(argv[msaaSamplesID + 1]);
			EngineSettings::settings->SetMSAASamples(msaaSamples);
			Debug::Log("MSAASample Override: " + std::to_string(msaaSamples), ALL);
		}
		catch (std::exception* e)
		{
			Debug::Log("Invalid -msaa flag. Skipping.", WARNINGS_ERRORS_ONLY);
		}
	}
#pragma endregion

#pragma region Window Name Override
	int windowNameID;
	if ((windowNameID = GetFlag("-name", argc, argv)) != -1 && argc > windowNameID + 1 && argv[windowNameID + 1][0] != '-')
	{

		EngineSettings::settings->SetWindowName(argv[windowNameID + 1]);
		Debug::Log("WindowName Override: " + std::string(argv[windowNameID + 1]), ALL);


	}
#pragma endregion
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
	OverrideEngineSettings(argc, argv);

	if(GetFlag("-forceWindow", argc, argv) != -1)
		EngineSettings::settings->SetWindowMode(true); //Shortcut to -windowMode 1
	MapBuilder::editorMode = GetFlag("-editor", argc, argv) != -1;
	
	PlayerController::_enableCheats = MapBuilder::editorMode;
	PlayerController::_godMode = MapBuilder::editorMode;

	//int t;
	//std::cin >> t;

	Debug::Log("Starting Game...", WARNINGS_ERRORS_LOG1);
	Debug::Log("with ArgCount: " + std::to_string(argc), WARNINGS_ERRORS_LOG2);


	AbstractGame* game = new MGEDemo(argc, argv);

	game->initialize();


	game->run();

	delete game;

	return 0;
}



