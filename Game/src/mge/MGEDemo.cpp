#include <iostream>
#include <string>

#include "glm.hpp"

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

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo(int argc, char *argv[]) :AbstractGame(), _hud(0)
{
	this->argc = argc;
	this->argv = std::vector<std::string>();
	for (size_t i = 0; i < argc; i++)
	{
		this->argv.push_back(argv[i]);
	}

}

void MGEDemo::initialize() {
	//setup the core part
	AbstractGame::initialize();

	
}

void MGEDemo::_initializeResources()
{



#pragma region GameSetup

	ScoreManager * scoreManager = new ScoreManager();
	scoreManager->GetScores();
	Mesh* testQuad = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");


	AbstractMaterial* backGroundMaterial = new AnimationMaterial(Texture::load(config::MGE_TEXTURE_PATH + "backg.png"), 4);
	Texture* rstonetex = Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png");
	Texture* sprstonetex = Texture::load(config::MGE_TEXTURE_PATH + "sp_runicfloor.png");
	Texture* emrstonetex = Texture::load(config::MGE_TEXTURE_PATH + "em_runicfloor.png");

	//add camera first (it will be updated last)
	


	Texture* planetTexture = Texture::load(config::MGE_TEXTURE_PATH + "ground.png");
	Texture* black = Texture::load(config::MGE_TEXTURE_PATH + "black.png");
	Texture* testTex = Texture::load(config::MGE_TEXTURE_PATH + "testTex.png");
	Texture* testNormal = Texture::load(config::MGE_TEXTURE_PATH + "testNormal.png");
	AbstractMaterial* runicPlaneMaterial = new TextureMovingMaterial(testTex, black, black, testNormal, 2, 1, 5, 2);


	Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane_8192.obj");
	//add the floor
	GameObject* plane = new GameObject("plane", glm::vec3(0, -1, 0));
	//plane->addBehaviour(new StaticBoxCollider(1, 0, 1));
	plane->scale(glm::vec3(150, 150, 150));
	plane->setMesh(planeMeshDefault);
	plane->setMaterial(runicPlaneMaterial);
	_world->add(plane);

	GameObject * BackGroundImage = new GameObject("background image", glm::vec3(0, 0, -1000));

	BackGroundImage->setMesh(testQuad);
	BackGroundImage->setMaterial(backGroundMaterial);
	BackGroundImage->scale(glm::vec3(1920, 1080, 1));
	BackGroundImage->rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	_world->add(BackGroundImage);

	Mesh* sphereMeshS = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");


	AbstractMaterial* runicStoneMaterial = new TextureMaterial(testTex, nullptr, nullptr, testNormal, 2, 1, 5, 2);
	GameObject* sphere = new GameObject("sphere", glm::vec3(0, 0, 0));
	sphere->addBehaviour(new DynamicBoxCollider(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5, 0.5, 0.5)));
	sphere->setMesh(sphereMeshS);
	sphere->setMaterial(runicStoneMaterial);

	sphere->addBehaviour(new PlayerController());
	_world->add(sphere);
	sphere->add(_world->getMainCamera());
	_world->getMainCamera()->setLocalPosition(glm::vec3(0, 5, 8));


	DataManager::instance->SetPlayer(sphere);
	DataManager::instance->SetBackground(BackGroundImage);
	DataManager::instance->SetGround(plane);




	//MESHES


	std::string filename = "maplist.lua";
	LevelManager* lm = nullptr;
	bool isRaw;
	std::string test = argv[0];
	GameStateManager::GameState gs = GameStateManager::StateMenu;

	if (argc == 2)
	{
		isRaw = false;
		gs = GameStateManager::StateGame;
		filename = argv[1];
	}
	else if (argc > 2)
	{
		filename = argv[1];
		isRaw = argv[2][0] == 'r';

		gs = GameStateManager::StateGame;
	}
	else
	{
		lm = new LevelManager(filename);

	}

	_loadingScreen->Update();

	if (lm != nullptr)lm->ChangeLevel(0);
	else Level* level = isRaw ? new Level(true, filename) : new Level(config::MGE_MAP_PATH + filename);

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
	m->diffuse = Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png");
	m->normal = Texture::load(config::MGE_TEXTURE_PATH + "testNormal.png");
	m->specular = Texture::load(config::MGE_TEXTURE_PATH + "testSpecular.png");
	_loadingScreen->Update();
	m->shininess = 1;
	m->maxHeight = 0;
	Texture* white = Texture::load(config::MGE_TEXTURE_PATH + "white.png");
	_loadingScreen->Update();
	//create some materials to display the cube, the plane and the light
	AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));

	AbstractMaterial* runicMihai = new AnimationMaterial(Texture::load(config::MGE_TEXTURE_PATH + "animtest.png"), 4);;
	//SCENE SETUP

	ScriptableLuaObject::Initialize(config::LUA_OBJECT_SCRIPT_FOLDER);
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

	ParticleEmitter * particleEm = new ParticleEmitter(particle, Texture::load(config::MGE_TEXTURE_PATH + "testParticle.png"), 150);

	GameObject* testParticle = new GameObject("particle", glm::vec3(0, 10, 0));
	testParticle->setMesh(testQuad);
	testParticle->setMaterial((AbstractMaterial*)particleEm);

	testParticle->scale(glm::vec3(0.5, 0.5, 0.5));
	_world->add(testParticle);
	//particleEm->Start();


	//add a spinning sphere
	

	GameObject * playerAnimation = new GameObject("playerAnimation", glm::vec3(0, 5, 0));

	playerAnimation->setMesh(testQuad);
	playerAnimation->setMaterial(runicMihai);
	playerAnimation->scale(glm::vec3(1, 1, 1));
	playerAnimation->rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	_world->add(playerAnimation);

	AnimationMaterial* caster = dynamic_cast<AnimationMaterial*>(runicMihai);
	caster->NextFrame();
	caster->NextFrame();
	caster->NextFrame();
	caster->NextFrame();




	//background->setLocalPosition(glm::vec3(0, 7, 0));

	//add a light. Note that the light does ABSOLUTELY ZIP! NADA ! NOTHING !
	//It's here as a place holder to get you started.
	//Note how the texture material is able to detect the number of lights in the scene
	//even though it doesn't implement any lighting yet!

	LightParams* params = new LightParams();

	Light* light = new Light("light", glm::vec3(0, 1, 0));
	light->SetParams(*params);
	light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->setMesh(cubeMeshF);
	light->setMaterial(lightMaterial);
	light->addBehaviour(new KeysBehaviour(25));
	_world->add(light);



	GameObject* cont = MapBuilder::instance->GetContainer();
	cont->setLocalPosition(glm::vec3(0, 0, -60));
	//cont->addBehaviour(new KeysBehaviour());
	_world->add(cont);
	//particleEm->Start();

#pragma endregion

	
}

//build the game _world
void MGEDemo::_initializeScene()
{
	//HUD Setup

#pragma region First Setup

	Camera* camera = new Camera("camera", glm::vec3(0, 1, 0));
	camera->rotate(glm::radians(-15.0f), glm::vec3(1, 0, 0));

	_world->setMainCamera(camera);

	DataManager * dataManager = new DataManager();

	

	GameStateManager * gameStateManager = new GameStateManager(GameStateManager::StateLoad);
	AudioManager * audioManager = new AudioManager();


#pragma endregion


	StoryPanelHandler * storyPanelHandler = new StoryPanelHandler();

	//setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	_menu = new Menu(_window);
	_storyPanel = new StoryPanel(_window);
	_gameOverScreen = new GameOverScreen(_window);
	_stageClear = new StageClear(_window);
	_winScreen = new WinScreen(_window);
	_loadingScreen = new LoadingScreen(_window);

	std::cout << "HUD initialized." << std::endl << std::endl;


	GameStateManager::instance->_state = GameStateManager::StateLoad;

}

void MGEDemo::_render(int pass) {
	
	AbstractGame::_render(pass);
	if (GameStateManager::instance->_state == GameStateManager::StateGame) _updateHud();
	else if (GameStateManager::instance->_state == GameStateManager::StateMenu) {
		_menu->Update();
		_storyPanel->Reset();     //could be solved more optimized
	}
	else if (GameStateManager::instance->_state == GameStateManager::StatePanel) _storyPanel->Update();
	else if (GameStateManager::instance->_state == GameStateManager::StateGameOver)_gameOverScreen->Update();
	else if (GameStateManager::instance->_state == GameStateManager::StateNextStage)_stageClear->Update();
	else if (GameStateManager::instance->_state == GameStateManager::StateWin)_winScreen->Update();
	else if (GameStateManager::instance->_state == GameStateManager::StateLoad)_loadingScreen->Update();
	if (_initFrame == 3)
	{
		_initFrame = -1;
		_initializeResources();
		
		GameStateManager::instance->_state = GameStateManager::StateMenu;
		
	}
	else if(_initFrame != -1)
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
