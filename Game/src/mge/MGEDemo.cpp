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
#include "../_vs2015/GameMaterial.hpp"

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

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo() :AbstractGame(), _hud(0)
{

	ScriptableLuaObject::Initialize(config::LUA_OBJECT_SCRIPT_FOLDER);

}

void MGEDemo::initialize() {
	//setup the core part
	AbstractGame::initialize();

	//setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	_menu = new Menu(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void MGEDemo::_initializeScene()
{
	//MESHES

	//load a bunch of meshes we will be using throughout this demo
	//each mesh only has to be loaded once, but can be used multiple times:
	//F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
	Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane_8192.obj");
	Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	Mesh* sphereMeshS = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

	//MATERIALS
	Material* m = new Material();
	m->diffuse = Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png");
	m->normal = Texture::load(config::MGE_TEXTURE_PATH + "testNormal.png");
	m->specular = Texture::load(config::MGE_TEXTURE_PATH + "testSpecular.png");
	m->shininess = 1;
	m->maxHeight = 0;
	AbstractMaterial* test = new GameMaterial(*m);
	Texture* rstonetex = Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png");
	Texture* sprstonetex = Texture::load(config::MGE_TEXTURE_PATH + "sp_runicfloor.png");
	Texture* emrstonetex = Texture::load(config::MGE_TEXTURE_PATH + "em_runicfloor.png");
	Texture* white = Texture::load(config::MGE_TEXTURE_PATH + "white.png");
	Texture* black = Texture::load(config::MGE_TEXTURE_PATH + "black.png");
	//create some materials to display the cube, the plane and the light
	AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));
	AbstractMaterial* runicPlaneMaterial = new TextureMovingMaterial(rstonetex, emrstonetex, sprstonetex, 2, 10, 1, 5, 2);
	AbstractMaterial* runicStoneMaterial = new TextureMaterial(rstonetex, emrstonetex, sprstonetex, 2, 10, 1, 5, 2);

	AbstractMaterial* runicMihai = new AnimationMaterial(Texture::load(config::MGE_TEXTURE_PATH + "animtest.png"), 4);
	//SCENE SETUP

   //add camera first (it will be updated last)
	Camera* camera = new Camera("camera", glm::vec3(0, 1, 0));
	camera->rotate(glm::radians(-30.0f), glm::vec3(1, 0, 0));

	_world->setMainCamera(camera);

	//add the floor
	GameObject* plane = new GameObject("plane", glm::vec3(-75, -1, -75));
	//plane->addBehaviour(new StaticBoxCollider(1, 0, 1));
	plane->scale(glm::vec3(150, 150, 150));
	plane->setMesh(planeMeshDefault);
	plane->setMaterial(runicPlaneMaterial);
	_world->add(plane);


	//add a spinning sphere
	GameObject* sphere = new GameObject("sphere", glm::vec3(0, 0, 0));
	sphere->addBehaviour(new DynamicBoxCollider(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1)));
	sphere->setMesh(sphereMeshS);
	sphere->setMaterial(runicStoneMaterial);

	sphere->addBehaviour(new PlayerController());
	_world->add(sphere);
	sphere->add(camera);
	camera->setLocalPosition(glm::vec3(0, 8, 12));

	GameObject * playerAnimation = new GameObject("playerAnimation", glm::vec3(0, 5, 0));

	playerAnimation->setMesh(planeMeshDefault);
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

	Light* light = new Light("light", glm::vec3(0, 4, 0));
	light->SetParams(*params);
	light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->setMesh(cubeMeshF);
	light->setMaterial(lightMaterial);
	light->addBehaviour(new KeysBehaviour(25));
	_world->add(light);
	std::vector<Biome*> biomes = std::vector<Biome*>();
	std::vector<std::string> biomeFiles = FileLoader::GetFilesFromFolder(config::MGE_BIOME_PATH);
	for (size_t i = 0; i < biomeFiles.size(); i++)
	{
		biomes.push_back(new Biome(biomeFiles[i]));
	}
	new BiomeHandler(biomes);
	GameObject* cont = MapBuilder::instance->GetContainer();
	cont->setLocalPosition(glm::vec3(0, 0, -60));
	//cont->addBehaviour(new KeysBehaviour());
	_world->add(cont);

}

void MGEDemo::_render() {
	AbstractGame::_render();
	if (GameStateManager::instance->_state == GameStateManager::StateGame) { 
		_updateHud();
	}
	if(GameStateManager::instance->_state == GameStateManager::StateMenu) _menu->Update();
}

void MGEDemo::_updateHud() {
	std::string debugInfo = "";
	debugInfo += std::string("Active Instances: ") + std::to_string(BiomeHandler::instance->GetTotalActiveInstances()) + '\n' + std::string("Instances:") + std::to_string(BiomeHandler::instance->GetTotalInstances()) + "\n" + std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}

MGEDemo::~MGEDemo()
{
	//dtor
}
