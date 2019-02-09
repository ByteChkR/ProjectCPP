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
#include "../_vs2015/Material.hpp"
#include "../_vs2015/GameMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

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
//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame (),_hud(0)
{
}

void MGEDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void MGEDemo::_initializeScene()
{
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load (config::MGE_MODEL_PATH+"plane.obj");
    Mesh* cubeMeshF = Mesh::load (config::MGE_MODEL_PATH+"cube_flat.obj");
    Mesh* sphereMeshS = Mesh::load (config::MGE_MODEL_PATH+"sphere_smooth.obj");

    //MATERIALS
	Material* m = new Material();
	m->diffuse = Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png");
	m->normal = Texture::load(config::MGE_TEXTURE_PATH + "testNormal.png");
	m->specular = Texture::load(config::MGE_TEXTURE_PATH + "testSpecular.png");
	m->shininess = 1;
	m->maxHeight = 0;
	AbstractMaterial* test = new GameMaterial(*m);
    //create some materials to display the cube, the plane and the light
    AbstractMaterial* lightMaterial = new ColorMaterial (glm::vec3(1,1,0));
	AbstractMaterial* runicPlaneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"), 100, 10, 1, 1, 10);
	AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"), 2, 10, 0, 5, 2);

    //SCENE SETUP

   //add camera first (it will be updated last)
    Camera* camera = new Camera ("camera", glm::vec3(0,1,0));
    camera->rotate(glm::radians(-30.0f), glm::vec3(1,0,0));
    
    _world->setMainCamera(camera);

    //add the floor
    GameObject* plane = new GameObject ("plane", glm::vec3(0,0,0));
	plane->addBehaviour(new StaticBoxCollider(1, 0, 1));
    plane->scale(glm::vec3(5,5,5));
    plane->setMesh(planeMeshDefault);
    plane->setMaterial(runicPlaneMaterial);
    //_world->add(plane);

    //add a spinning sphere
    GameObject* sphere = new GameObject ("sphere", glm::vec3(0,0,0));
	sphere->addBehaviour(new DynamicBoxCollider(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1)));
    sphere->setMesh (sphereMeshS);
    sphere->setMaterial(runicStoneMaterial);
    sphere->addBehaviour (new PlayerController());
    _world->add(sphere);
	sphere->add(camera);
	camera->setLocalPosition(glm::vec3(0, 8, 12));

    //add a light. Note that the light does ABSOLUTELY ZIP! NADA ! NOTHING !
    //It's here as a place holder to get you started.
    //Note how the texture material is able to detect the number of lights in the scene
    //even though it doesn't implement any lighting yet!

	LightParams* params = new LightParams();

    Light* light = new Light("light", glm::vec3(0,4,0));
	light->SetParams(*params);
    light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
    light->setMesh(cubeMeshF);
    light->setMaterial(lightMaterial);
    light->addBehaviour(new KeysBehaviour(25));
	_world->add(light);
	new PresetHandler(std::vector<std::string>());
	mb = new MapBuilder(50, 15);
	GameObject* cont = mb->GetContainer();
	cont->setLocalPosition(glm::vec3(0, 0, -60));
	//cont->addBehaviour(new KeysBehaviour());
	_world->add(cont);
	
}

void MGEDemo::_render() {
    AbstractGame::_render();
	mb->Update();
    _updateHud();
}

void MGEDemo::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string("Instances:") + std::to_string(PresetHandler::instance->GetTotalInstances()) + "\n" +std::string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

MGEDemo::~MGEDemo()
{
	//dtor
}
