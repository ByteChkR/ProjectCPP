#include <iostream>

#include "../_vs2015/GameStateManager.h"
#include "../_vs2015/ParticleSystem.h"

#include "AbstractGame.hpp"
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "mge/util/AudioManager.h"
#include "../_vs2015/Debug.h"
#include "mge/config.hpp"
#include "SFML/Graphics.hpp"
#include "..\_vs2015\EngineSettings.h"
AbstractGame* AbstractGame::instance = nullptr;

AbstractGame::AbstractGame() :_window(NULL), _renderer(NULL), _world(NULL), _fps(0), startupTime(0)
{
	CurrentGameMode = STORY;
	timeScale = 1;
	instance = this;
	_particleSystem = new ParticleSystem();
	fallbackTexture = new sf::Image();
	fallbackTexture->loadFromFile(config::MGE_TEXTURE_PATH + "fallbacktexture.png");

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
	Debug::Log("Initializing engine...", WARNINGS_ERRORS_LOG1);
	_initializeWindow();
	_printVersionInfo();
	_initializeGlew();
	_initializeRenderer();
	_initializeCollisionManager();
	_initializeWorld();
	_initializeScene();

	Debug::Log("Engine initialized.", WARNINGS_ERRORS_LOG1);
}

///SETUP

void AbstractGame::_initializeWindow() {
	Debug::Log("Initializing window...", WARNINGS_ERRORS_LOG1);
	sf::ContextSettings cs = sf::ContextSettings(24, 8, EngineSettings::settings->GetMSAASampleCount(), 3, 3);

	sf::VideoMode videoMode = sf::VideoMode(EngineSettings::settings->GetWidth(), EngineSettings::settings->GetHeight());


	_window = new sf::RenderWindow(videoMode, EngineSettings::settings->GetWindowName(),
		EngineSettings::settings->GetWindowMode() ? sf::Style::Default : sf::Style::Fullscreen, cs);
	glEnable(GL_MULTISAMPLE);
	_window->setVerticalSyncEnabled(EngineSettings::settings->GetVSyncEnabled());
	Debug::Log("Window initialized.", WARNINGS_ERRORS_LOG1);
}

float AbstractGame::GetTimeSinceStartup()
{
	return startupTime;
}

void AbstractGame::_printVersionInfo() {
	Debug::Log("Context info:", WARNINGS_ERRORS_LOG3);
	Debug::Log("----------------------------------", WARNINGS_ERRORS_LOG3);
	//print some debug stats for whoever cares
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	//nice consistency here in the way OpenGl retrieves values
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	if (config::DEBUG_LEVEL >= WARNINGS_ERRORS_LOG3)
	{

		printf("GL Vendor : %s\n", vendor);
		printf("GL Renderer : %s\n", renderer);
		printf("GL Version (string) : %s\n", version);
		printf("GL Version (integer) : %d.%d\n", major, minor);
		printf("GLSL Version : %s\n", glslVersion);

	}
	Debug::Log("----------------------------------", WARNINGS_ERRORS_LOG3);
}

void AbstractGame::_initializeGlew() {
	Debug::Log("Initializing GLEW...", WARNINGS_ERRORS_LOG1);
	//initialize the opengl extension wrangler
	GLint glewStatus = glewInit();
	Debug::Log("Initialized GLEW, status (1 == OK, 0 == FAILED):" + std::to_string(glewStatus == GLEW_OK), WARNINGS_ERRORS_LOG2);
}

void AbstractGame::_initializeRenderer() {
	//setup our own renderer
	Debug::Log("Initializing renderer...", WARNINGS_ERRORS_LOG1);

	_renderer = new Renderer(true);

	_renderer->setClearColor(0, 0, 0);
	Debug::Log("Renderer done.", WARNINGS_ERRORS_LOG1);
}

void AbstractGame::_initializeWorld() {
	//setup the world
	Debug::Log("Initializing world...", WARNINGS_ERRORS_LOG1);
	_world = new World();
	Debug::Log("World initialized.", WARNINGS_ERRORS_LOG1);
}

void AbstractGame::_initializeCollisionManager()
{
	Debug::Log("Initializing Collision Manager...", WARNINGS_ERRORS_LOG1);
	_manager = new CollisionManager();
	Debug::Log("Collision Manager initialized.", WARNINGS_ERRORS_LOG1);

}

float AbstractGame::GetTimeSinceLastFrame()
{
	Debug::Log(std::to_string(timeSinceLastUpdate.asSeconds()), ALL);
	return timeSinceLastUpdate.asSeconds();
}

float AbstractGame::GetDeltaTime()
{
	return lastDT;
}

///MAIN GAME LOOP

void AbstractGame::run()
{

	//setting to calculate fps
	sf::Clock renderClock;
	int frameCount = 0;
	float timeSinceLastFPSCalculation = 0;

	//settings to make sure the update loop runs at 60 fps
	sf::Time timePerFrame = sf::seconds(1.0f / EngineSettings::settings->GetFPSTarget());
	sf::Clock updateClock;
	timeSinceLastUpdate = sf::Time::Zero;

	while (_window->isOpen()) {
		timeSinceLastUpdate += updateClock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			while (timeSinceLastUpdate > timePerFrame) {
				startupTime += timePerFrame.asSeconds();
				timeSinceLastUpdate -= timePerFrame;
				float tpf = timePerFrame.asSeconds() / timeScale;
				_update(tpf);
				lastDT = tpf;
				_manager->Update(tpf);
			}


			AudioManager::instance->Update(timePerFrame.asSeconds());

			_render(0);
			_render(1);
			_window->display();

			//fps count is updated once every 1 second
			frameCount++;

			timeSinceLastFPSCalculation += renderClock.restart().asSeconds();
			if (timeSinceLastFPSCalculation > 1) {
				_fps = frameCount / timeSinceLastFPSCalculation;
				timeSinceLastFPSCalculation -= 1;
				frameCount = 0;
			}

		}

		//empty the event queue
		_processEvents();
	}
}

void AbstractGame::SetTimeScale(float scale)
{
	timeScale = scale;
}

float AbstractGame::GetTimeScale()
{
	return timeScale;
}

void AbstractGame::_update(float pStep) {
	_particleSystem->Update(pStep);
	GameStateManager::instance->Update(pStep, _world);
}

void AbstractGame::_render(int pass) {
	_renderer->render(pass, _world);
}

void AbstractGame::_processEvents()
{
	sf::Event event;
	bool exit = false;

	//we must empty the event queue
	while (_window->pollEvent(event)) {
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
				//exit = true;
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



