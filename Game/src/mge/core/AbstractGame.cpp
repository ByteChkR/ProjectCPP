#include <iostream>

#include "../_vs2015/GameStateManager.h"
#include "../_vs2015/ParticleSystem.h"

#include "AbstractGame.hpp"
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "mge/util/AudioManager.h"

AbstractGame* AbstractGame::instance = nullptr;

AbstractGame::AbstractGame():_window(NULL),_renderer(NULL),_world(NULL), _fps(0), startupTime(0)
{
	instance = this;
	_particleSystem = new ParticleSystem();
    //ctor
}

AbstractGame::~AbstractGame()
{
    //dtor
    delete _window;
    delete _renderer;
    delete _world;
}

void AbstractGame::initialize() {
    std::cout << "Initializing engine..." << std::endl << std::endl;
    _initializeWindow();
    _printVersionInfo();
    _initializeGlew();
    _initializeRenderer();
	_initializeCollisionManager();
    _initializeWorld();
    _initializeScene();
	
    std::cout << std::endl << "Engine initialized." << std::endl << std::endl;
}

///SETUP

void AbstractGame::_initializeWindow() {
	std::cout << "Initializing window..." << std::endl;
	sf::ContextSettings cs = sf::ContextSettings(24, 8, 8, 3, 3);
	_window = new sf::RenderWindow( sf::VideoMode(900,600), "My Game!", sf::Style::Default, cs);
	glEnable(GL_MULTISAMPLE);
	//_window->setVerticalSyncEnabled(true);
    std::cout << "Window initialized." << std::endl << std::endl;
}

float AbstractGame::GetTimeSinceStartup()
{
	return startupTime;
}

void AbstractGame::_printVersionInfo() {
	std::cout << "Context info:" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    //print some debug stats for whoever cares
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
    //nice consistency here in the way OpenGl retrieves values
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Vendor : %s\n", vendor);
    printf("GL Renderer : %s\n", renderer);
    printf("GL Version (string) : %s\n", version);
    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);

    std::cout << "----------------------------------" << std::endl << std::endl;
}

void AbstractGame::_initializeGlew() {
	std::cout << "Initializing GLEW..." << std::endl;
    //initialize the opengl extension wrangler
    GLint glewStatus = glewInit();
	std::cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << std::endl << std::endl;
}

void AbstractGame::_initializeRenderer() {
    //setup our own renderer
	std::cout << "Initializing renderer..." << std::endl;
	_renderer = new Renderer(true);
    _renderer->setClearColor(0,0,0);
    std::cout << "Renderer done." << std::endl << std::endl;
}

void AbstractGame::_initializeWorld() {
    //setup the world
	std::cout << "Initializing world..." << std::endl;
	_world = new World();
    std::cout << "World initialized." << std::endl << std::endl;
}

void AbstractGame::_initializeCollisionManager()
{
	std::cout << "Initializing Collision Manager..."<<std::endl;
	_manager = new CollisionManager();
	std::cout << "Collision Manager initialized." << std::endl;

}

///MAIN GAME LOOP

void AbstractGame::run()
{
	
    //setting to calculate fps
	sf::Clock renderClock;
    int frameCount = 0;
    float timeSinceLastFPSCalculation = 0;

	//settings to make sure the update loop runs at 60 fps
	sf::Time timePerFrame = sf::seconds(1.0f / 120.0f);
	sf::Clock updateClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (_window->isOpen()) {
		timeSinceLastUpdate += updateClock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			startupTime += timeSinceLastUpdate.asSeconds();
		    while (timeSinceLastUpdate > timePerFrame) {
                timeSinceLastUpdate -= timePerFrame;
                _update(timePerFrame.asSeconds());
				_manager->Update(timePerFrame.asSeconds());
		    }


			AudioManager::instance->Update(timePerFrame.asSeconds());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				AudioManager::instance->ChangeBackgroundMusic(0);

			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				AudioManager::instance->ChangeBackgroundMusic(1);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				AudioManager::instance->ChangeBackgroundMusic(2);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			{
				AudioManager::instance->GameOver();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			{
				AudioManager::instance->Restart(0);
			}

            _render(0);
			_render(1);
            _window->display();

            //fps count is updated once every 1 second
            frameCount++;
			
            timeSinceLastFPSCalculation += renderClock.restart().asSeconds();
            if (timeSinceLastFPSCalculation > 1) {
                _fps = frameCount/timeSinceLastFPSCalculation;
                timeSinceLastFPSCalculation -= 1;
                frameCount = 0;
            }

		}

		//empty the event queue
		_processEvents();
    }
}

void AbstractGame::_update(float pStep) {
	_particleSystem->Update(pStep);
	GameStateManager::instance->Update(pStep,_world);
}

void AbstractGame::_render (int pass) {
    _renderer->render(pass, _world);
}

void AbstractGame::_processEvents()
{
	sf::Event event;
	bool exit = false;

	//we must empty the event queue
	while( _window->pollEvent( event ) ) {
        //give all system event listeners a chance to handle events
        //optionally to be implemented by you for example you could implement a
        //SystemEventDispatcher / SystemEventListener pair which allows Listeners to
        //register with the dispatcher and then do something like:
        //SystemEventDispatcher::dispatchEvent(event);

        switch (event.type) {
            case sf::Event::Closed:
                exit = true;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    exit = true;
                }
                break;
            case sf::Event::Resized:
                //would be better to move this to the renderer
                //this version implements nonconstrained match viewport scaling
                glViewport(0, 0, event.size.width, event.size.height);
                break;

            default:
                break;
        }
	}

	if (exit) {
        _window->close();
	}
}



