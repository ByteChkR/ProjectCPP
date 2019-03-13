#include <iostream>
#include <string>

#include "glm.hpp"
#include "../_vs2015/Debug.h"
#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge\materials\AnimationMaterial.hpp"
#include "../_vs2015/TextureMovingMaterial.h"
#include "../_vs2015/Material.hpp"
#include "mge/util/AudioManager.h"
#include "mge/util/DataManager.h"
#include "../_vs2015/StoryPanelHandler.h"
#include "../_vs2015/LevelManager.h"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

#include "mge/util/BiomeHandler.h"
#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"

#include "../_vs2015/AbstractStaticCollider.hpp"
#include "../_vs2015/CollisionManager.hpp"
#include "../_vs2015/DynamicBoxCollider.hpp"
#include "../_vs2015/StaticBoxCollider.hpp"
#include "../_vs2015/PlayerController.hpp"
#include "../_vs2015/MapBuilder.h"
#include "../_vs2015/PresetHandler.hpp"
#include "../_vs2015/ScriptableLuaObject.h"
#include "../_vs2015/GameStateManager.h"
#include "../_vs2015/ParticleSystem.h"
#include "../_vs2015/ParticleEmitter.h"

#include "mge/util/ScoreManager.h"
#include "mge/util/DataManager.h"
#include "../_vs2015/KeyLogger.h"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo(int argc, char *argv[]) :AbstractGame(), _hud(0)
{
	_noStory = false;
	this->argc = argc;
	this->argv = std::vector<std::string>();
	for (int i = 0; i < argc; i++)
	{
		Debug::Log("Parameter " + std::to_string(i) + ": " + argv[i], ALL);
		this->argv.push_back(argv[i]);
	}
	klogger = new KeyLogger();
}

void MGEDemo::initialize() {
	//setup the core part
	AbstractGame::initialize();


}

void MGEDemo::_initializeResources()
{



#pragma region GameSetup

	ScoreManager * scoreManager = new ScoreManager();
	Mesh* testQuad = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");


	AbstractMaterial* backGroundMaterial = new AnimationMaterial(Texture::load(config::MGE_TEXTURE_PATH + "backg.png", true), 1);
	Texture* rstonetex = Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png", true);
	Texture* sprstonetex = Texture::load(config::MGE_TEXTURE_PATH + "sp_runicfloor.png", false);
	Texture* emrstonetex = Texture::load(config::MGE_TEXTURE_PATH + "em_runicfloor.png", false);

	//add camera first (it will be updated last)



	Texture* planetTexture = Texture::load(config::MGE_TEXTURE_PATH + "ground.png", true);
	Texture* black = Texture::load(config::MGE_TEXTURE_PATH + "black.png", false);
	Texture* testTex = Texture::load(config::MGE_TEXTURE_PATH + "testTex.png", true);
	Texture* testNormal = Texture::load(config::MGE_TEXTURE_PATH + "testNormal.png", false);
	AbstractMaterial* runicPlaneMaterial = new TextureMovingMaterial(testTex, black, black, 2, 1, 5, 2);


	Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane_8192.obj");
	//add the floor
	GameObject* plane = new GameObject("plane", glm::vec3(0, -1, 0));
	//plane->addBehaviour(new StaticBoxCollider(1, 0, 1));
	plane->scale(glm::vec3(150, 150, 150));
	plane->setMesh(planeMeshDefault);
	plane->setMaterial(runicPlaneMaterial);
	_world->add(plane);

	GameObject * BackGroundImage = new GameObject("background image", glm::vec3(0, 100, -1000));

	BackGroundImage->setMesh(testQuad);
	BackGroundImage->setMaterial(backGroundMaterial);
	BackGroundImage->scale(glm::vec3(1920 / 2.3f, 1080 / 2.3f, 1));
	BackGroundImage->rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	_world->add(BackGroundImage);

	Mesh* sphereMeshS = Mesh::load(config::MGE_MODEL_PATH + "placeholder.obj");


	AbstractMaterial* runicStoneMaterial = new TextureMaterial(testTex, nullptr, nullptr, 2, 1, 5, 2);
	GameObject* playerObject = new GameObject("sphere", glm::vec3(0, 0, 0));
	playerObject->addBehaviour(new DynamicBoxCollider(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1)));
	//playerObject->setMesh(sphereMeshS);
	//playerObject->setMaterial(runicStoneMaterial);

	AbstractMaterial* runicMihai = new AnimationMaterial(Texture::load(config::MGE_TEXTURE_PATH + (EngineSettings::settings->GetWednesdayMode() ? "helicopter1.png" : "helicopter.png"), true), 1);;

	AbstractMaterial* heliDropTexture = new AnimationMaterial(Texture::load(config::MGE_TEXTURE_PATH + (EngineSettings::settings->GetWednesdayMode() ? "crate.png" : "crate.png"), true), 1);;


	GameObject * heliAnimation = new GameObject("HeliAnimation", glm::vec3(0, 5, 0));
	heliAnimation->setMesh(testQuad);
	heliAnimation->setMaterial(runicMihai);
	heliAnimation->scale(glm::vec3(10, 10, 10));
	heliAnimation->setLocalPosition(glm::vec3(10, 30, -150));
	heliAnimation->rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	_world->add(heliAnimation);

	GameObject * heliDrop = new GameObject("HeliAnimation", glm::vec3(0, 5, 0));
	heliDrop->setMesh(testQuad);
	heliDrop->setMaterial(heliDropTexture);
	heliDrop->scale(glm::vec3(2,2, 2));
	heliDrop->setLocalPosition(glm::vec3(-200, -220, -210));
	heliDrop->rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	_world->add(heliDrop);



	_world->add(playerObject);
	playerObject->addBehaviour(new PlayerController(playerObject, heliAnimation, heliDrop));
	playerObject->add(_world->getMainCamera());
	_world->getMainCamera()->setLocalPosition(PlayerController::CameraResetPosition);


	DataManager::instance->SetPlayer(playerObject);
	DataManager::instance->SetBackground(BackGroundImage);
	DataManager::instance->SetGround(plane);




	//MESHES


	Light* light = new Light("light", glm::vec3(-100, 100, 100));

	std::string mapFile = "";
	GameMode gMode = ProcessStartingFlags(&mapFile);
	CurrentGameMode = gMode;
	LevelManager* lm = nullptr;
	if (gMode == LEGACY)
	{
		Level* l = new Level(mapFile);
	}
	else if (gMode == LEGACY_R)
	{
		Level* l = new	Level(true, mapFile);
	}
	else if (gMode == STORY)
	{
		lm = new LevelManager("mge/maplist.lua", true);
	}
	else if (gMode == PLAYGROUND)
	{
		lm = new LevelManager(mapFile, false);
	}

	_loadingScreen->Update();

	if (lm != nullptr)lm->ChangeLevel(0);

	Particle* particle = new Particle();
	particle->color = glm::vec4(1, 1, 1, 1);//(R;G;B;A)
	particle->acceleration = glm::vec3(0, 0.6, 0);
	particle->gravity = 1.5;
	particle->life = 1.5;

	//ParticleEmitter * particleEm = new ParticleEmitter(particle, Texture::load(config::MGE_TEXTURE_PATH + "testParticle.png"), 150);

	//load a bunch of meshes we will be using throughout this demo
	//each mesh only has to be loaded once, but can be used multiple times:
	//F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
	Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");

	_loadingScreen->Update();
	//MATERIALS
	Material* m = new Material();
	m->diffuse = Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png", true);
	m->normal = Texture::load(config::MGE_TEXTURE_PATH + "testNormal.png", false);
	m->specular = Texture::load(config::MGE_TEXTURE_PATH + "testSpecular.png", false);
	_loadingScreen->Update();
	m->shininess = 1;
	m->maxHeight = 0;
	Texture* white = Texture::load(config::MGE_TEXTURE_PATH + "white.png", true);
	_loadingScreen->Update();
	//create some materials to display the cube, the plane and the light
	AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));


	//SCENE SETUP

	ScriptableLuaObject::Initialize(config::LUA_OBJECT_SCRIPT_FOLDER);
	sloFallback = ScriptableLuaObject::GetStructWithName("fallback");
	sloGameObjectFallback = ScriptableLuaObject::Instantiate("fallback");
	//Biome Setup
	std::vector<Biome*> biomes = std::vector<Biome*>();
	std::vector<std::string> biomeFiles = FileLoader::GetFilesFromFolder(config::MGE_BIOME_PATH);
	_loadingScreen->Update();
	for (size_t i = 0; i < biomeFiles.size(); i++)
	{
		biomes.push_back(new Biome(biomeFiles[i]));

		_loadingScreen->Update();
	}
	new BiomeHandler(biomes);

	_world->add(light);

	GameObject* cont = MapBuilder::instance->GetContainer();
	cont->setLocalPosition(glm::vec3(0, 0, -60));
	_world->add(cont);

#pragma endregion


}

MGEDemo::GameMode MGEDemo::ProcessStartingFlags(std::string* mapFile)
{

	GameMode gmode = STORY;
	if (!MapBuilder::editorMode)
	{
		PlayerController::_enableCheats = GetFlag("-enableCheats", argc, argv) != -1;
		PlayerController::_lastTutorial = (GetFlag("-noTutorial", argc, argv) == -1) ? -1 : 99;

		Debug::Log("Cheats Enabled: " + PlayerController::_enableCheats ? "YES" : "NO", ALL);
		Debug::Log("Ignore Tutorials Enabled: " + (PlayerController::_lastTutorial == 99) ? "YES" : "NO", ALL);
	}

	_noStory = GetFlag("-noStory", argc, argv) != -1 || MapBuilder::editorMode;

	*mapFile = "maplist.lua";

	if (GetFlag("-s", argc, argv) != -1)return gmode; //If -s is a parameter ignore anything else and start with story mode

	int legacyMapID = GetFlag("-l", argc, argv);
	if (legacyMapID != -1)
	{

		Debug::Log("Found Legacy Flag..", ALL);
		gmode = LEGACY;
		if (legacyMapID + 1 >= argc || argv[legacyMapID + 1][0] == '-')
		{
			Debug::LogError("Inavlid parameter for Legacy mode. Expected path to map after -l flag");
			Debug::LogError("Falling back to story mode.");
			gmode = STORY;
			return gmode;
		}
		*mapFile = argv[legacyMapID + 1];
		size_t test = mapFile->find_last_of(".");
		size_t find = mapFile->substr(test, mapFile->size() - test).find("txt");
		if (find != std::string::npos)
		{

			Debug::Log("Found Legacy Flag.. Detected NON Lua File", ALL);
			gmode = LEGACY_R;
		}


		Debug::Log("Found Legacy Flag..(" + *mapFile + ")", ALL);
		return gmode;
	}

	int playgroundFlagID = GetFlag("-p", argc, argv);

	if (playgroundFlagID != -1)
	{
		gmode = PLAYGROUND;
		if (playgroundFlagID + 1 >= argc || argv[playgroundFlagID + 1][0] == '-')
		{
			Debug::LogError("Inavlid parameter for Playground mode. Expected path to maplist after -p flag");
			Debug::LogError("Falling back to story mode.");
			gmode = STORY;
			return gmode;
		}
		*mapFile = argv[playgroundFlagID + 1];
		return gmode;
	}
	return gmode;

}


int MGEDemo::GetFlag(std::string flag, int argc, std::vector< std::string> argv)
{
	for (int i = 0; i < argc; i++)
	{

		if (argv[i] == flag)return i;

	}
	return -1;
}

//build the game _world
void MGEDemo::_initializeScene()
{
	//HUD Setup

#pragma region First Setup

	Camera* camera = new Camera("camera", glm::vec3(0, 1, 0));
	camera->rotate(glm::radians(-20.0f), glm::vec3(1, 0, 0));

	_world->setMainCamera(camera);

	DataManager * dataManager = new DataManager();



	GameStateManager * gameStateManager = new GameStateManager(GameStateManager::StateLoad);
	AudioManager * audioManager = new AudioManager();


#pragma endregion


	StoryPanelHandler * storyPanelHandler = new StoryPanelHandler();

	//setup the custom part so we can display some text
	Debug::Log("Initializing GUI", WARNINGS_ERRORS_LOG1);

	_hud = new DebugHud(_window);
	_menu = new Menu(_window);
	_storyPanel = new StoryPanel(_window);
	_gameOverScreen = new GameOverScreen(_window);
	_stageClear = new StageClear(_window);
	_winScreen = new WinScreen(_window);
	_loadingScreen = new LoadingScreen(_window);
	_scoreBoard = new ScoreBoard(_window);
	_credits = new Credits(_window);
	_tutorial0 = new Tutorial0(_window);
	_tutorial1 = new Tutorial1(_window);
	_tutorial2 = new Tutorial2(_window);
	_tutorial3 = new Tutorial3(_window);

	Debug::Log("GUI initialized.", WARNINGS_ERRORS_LOG1);

	/*
		GameStateManager::instance->_state = GameStateManager::StateLoad;*/

}

void MGEDemo::_render(int pass) {

	AbstractGame::_render(pass);
	if (GameStateManager::instance->_state == GameStateManager::StateGame) _updateHud();
	else if (GameStateManager::instance->_state == GameStateManager::StateMenu) {
		_menu->Update();
		std::string output;
		if (klogger->SFKey2String(&output))
		{
			Debug::Log(output, ALL);
		}
		PlayerController::instance->ResetTutorial();
		_storyPanel->Reset();
		_winScreen->ResetScoreSendBool();
		_scoreBoard->ResetScoreUpdate();
		//PlayerController::instance->ResetScore();
	}
	else if (GameStateManager::instance->_state >= GameStateManager::Tutorial1)
	{
		int num = GameStateManager::Tutorial1 - GameStateManager::instance->_state;
		if (num == 0)_tutorial0->Update();
		else if (num == -1)_tutorial1->Update();
		else if (num == -2)_tutorial2->Update();
		else if (num == -3)_tutorial3->Update();

		//tutorialArray[num].Update();
		//_updateHud();
	}
	else if (GameStateManager::instance->_state == GameStateManager::StatePanel)
	{
		if (CurrentGameMode != STORY || _noStory)
			GameStateManager::instance->_state = GameStateManager::StateGame;
		else _storyPanel->Update();
	}
	else if (GameStateManager::instance->_state == GameStateManager::StateGameOver)
	{
		_gameOverScreen->Update();
	}
	else if (GameStateManager::instance->_state == GameStateManager::StateNextStage)_stageClear->Update();
	else if (GameStateManager::instance->_state == GameStateManager::StateWin)_winScreen->Update();
	else if (GameStateManager::instance->_state == GameStateManager::StateLoad)_loadingScreen->Update();
	else if (GameStateManager::instance->_state == GameStateManager::StateCredits) _credits->Update();
	else if (GameStateManager::instance->_state == GameStateManager::StateScore) _scoreBoard->Update();
	if (_initFrame == 3)
	{
		_initFrame = -1;
		_initializeResources();

		GameStateManager::instance->_state = GameStateManager::StateMenu;

	}
	else if (_initFrame != -1)
		_initFrame++;
}

void MGEDemo::_updateHud() {
	std::string debugInfo = "";
	debugInfo += std::string("Active Instances: ") + std::to_string(BiomeHandler::instance->GetTotalActiveInstances()) + '\n' + std::string("Instances:") + std::to_string(BiomeHandler::instance->GetTotalInstances()) + "\n" + std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->Update();
}

MGEDemo::~MGEDemo()
{
	//dtor
}
