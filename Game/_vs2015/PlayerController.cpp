#include "PlayerController.hpp"
#include "SFML/Window.hpp"
#include "mge/util/MapGenerator.h"
#include "GameStateManager.h"
#include "MapBuilder.h"
#include "LevelManager.h"
#include "mge/core/Camera.hpp"
#include "mge/core/AbstractGame.hpp"
#include "mge/config.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge\materials\AnimationMaterial.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "StaticBoxCollider.hpp"
#include "mge/core/AbstractGame.hpp"
#include "Debug.h"
#include <stdlib.h> 
#include <time.h>
PlayerController* PlayerController::instance = nullptr;

PlayerController::PlayerController(GameObject * pOwner, GameObject * pHeli)
{
	srand((unsigned int)time(NULL));
	setOwner(pOwner);



	heli = pHeli;
	heliInitialPosition = heli->getLocalPosition();
	std::function<void()> oE = std::bind(&PlayerController::OnGameEnd, std::ref(*this));
	std::function<void(float)> oT = std::bind(&PlayerController::OnGameEndTick, std::ref(*this), std::placeholders::_1);

	std::function<void()> onDeathEnd = std::bind(&PlayerController::OnDeathEnd, std::ref(*this));
	std::function<void(float)> onDeathTick = std::bind(&PlayerController::OnDeathTick, std::ref(*this), std::placeholders::_1);

	_deathTimer = new Timer(onDeathTick, onDeathEnd, 0.5, "DeathTimer", false);
	_endOfGameTimer = new Timer(oT, oE, 2, "EndOfGameTimer", false);

	Particle* particle = new Particle();
	particle->color = glm::vec4(1, 1, 1, 1);//(R;G;B;A)
	particle->acceleration = glm::vec3(0, 0.6, 0);
	particle->gravity = 1.5;
	particle->life = 0.5;
	_deathParticle = new ParticleEmitter(particle, Texture::load(config::MGE_TEXTURE_PATH + "testParticle.png", true), 50, 50, false);

	_deathContainer = new GameObject("deathContainer", glm::vec3(0, 0, 0));

	_deathContainer->setMesh(Mesh::load(config::MGE_MODEL_PATH + "plane.obj"));
	_deathContainer->setMaterial((AbstractMaterial*)_deathParticle);
	_owner->add(_deathContainer);
	//_deathParticle->Start();
	_currentLane = 1;
	_gravity = -1;
	_gravityWhenGoingDown = -5;
	_isBackSwitching = false;
	_jumpForce = 0.45f;
	_velocity = 0;
	_switchTime = 0.1f;
	_lastTutorial = -1;
	lastLevelFinalScore = 0;
	_curSwitchTime = 0;
	_nextLane = -1;
	_coins = 0;
	_grounded = false;
	_isSwitching = false;
	_isJumping = true;
	_isGoingDown = false;
	_isAPressed = false;
	_isDPressed = false;
	_isWPRessed = false;
	_isStruggling = false;
	_struggleTime = 0;
	_struggleMaxTime = 2;
	gStruggleAnimation = new GameObject("StruggleAnim");
	gStruggleAnimation->addBehaviour(new RotatingBehaviour(3));
	GameObject * struggleObject = new GameObject("StruggleObject");
	struggleObject->setMaterial(new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "dizzystars_initialShadingGroup_AlbedoTransparency.png", true), nullptr, nullptr, 2, 1, 5, 2));
	struggleObject->setMesh(Mesh::load(config::MGE_MODEL_PATH + "dizzystars.obj"));
	struggleObject->setLocalPosition(glm::vec3(0, -2, 0));
	_owner->add(gStruggleAnimation);
	gStruggleAnimation->add(struggleObject);
	gStruggleAnimation->setLocalPosition(glm::vec3(0, 3, 0));
	gStruggleAnimation->DisableBehaviours();
	lastStruggleCollider = "";
	_lockControls = false;

	instance = this;

	createModels();
}

void PlayerController::ResetTutorial()
{
	_lastTutorial = -1;
}

void PlayerController::ResetScore(int newScore) {
	_coins = newScore;
	lastLevelFinalScore = newScore;
}

AbstractBehaviour* PlayerController::Clone()
{
	return new PlayerController(_owner, _owner);
}

PlayerController::~PlayerController()
{

}

void PlayerController::OnDeathEnd()
{
	//AbstractGame::instance->SetTimeScale(1);
	_deathParticle->Stop();
	_lockControls = false;
	_deathTimer->Reset();
	_owner->setLocalPosition(MapGenerator::instance->GetLaneAt(_currentLane)->GetPosition() + glm::vec3(0, 0, 0));
	_owner->add(AbstractGame::instance->_world->getMainCamera());
	AbstractGame::instance->_world->getMainCamera()->setLocalPosition(glm::vec3(0, 5, 8));
	_isStruggling = false;
	_struggleTime = 0;
	gStruggleAnimation->DisableBehaviours();
	_coins = lastLevelFinalScore;
	GameStateManager::instance->_state = GameStateManager::StateGameOver;
	_owner->DisableBehaviours();
	MapBuilder::instance->Unload();
	MapBuilder::instance->GetContainer()->setLocalPosition(glm::vec3(0, 0, 3)); //<--- therealchanger
	AudioManager::instance->PlaySound(0);


}

bool PlayerController::IsMoving()
{
	return (GameStateManager::instance->_state == GameStateManager::StateGame && !_endOfGameTimer->IsStarted() && !_deathTimer->IsStarted());
}

void PlayerController::OnDeathTick(float pTime)
{

	//_deathContainer->setLocalPosition(glm::vec3(0,1,0));
}

void PlayerController::OnGameEndTick(float pTime)
{

	_owner->setLocalPosition(_owner->getLocalPosition() + glm::vec3(0, 0, -0.5f)*pTime);
}

void PlayerController::SetCurrentLane(int lane)
{
	_currentLane = lane;
	_nextLane = lane;
	_owner->setLocalPosition(MapGenerator::instance->GetLaneAt(_currentLane)->GetPosition() + glm::vec3(0, 0, 0));//<---
	heliInitialPosition.x = _owner->getLocalPosition().x;
	MapBuilder::instance->GetContainer()->setLocalPosition(glm::vec3(0, 0, 3)); // therealchanger
}


int PlayerController::GetCoinCount()
{
	return _coins;
}

void PlayerController::OnGameEnd()
{
	_lockControls = false;
	_endOfGameTimer->Reset();
	_owner->setLocalPosition(MapGenerator::instance->GetLaneAt(_currentLane)->GetPosition() + glm::vec3(0, 0, 0));
	_owner->add(AbstractGame::instance->_world->getMainCamera());
	AbstractGame::instance->_world->getMainCamera()->setLocalPosition(glm::vec3(0, 5, 8));
	MapBuilder::instance->Unload();
	//LevelManager::instance->NextLevel();
	GameStateManager::instance->_state = GameStateManager::StateNextStage;
	MapBuilder::instance->GetContainer()->setLocalPosition(glm::vec3(0, 0, 3)); // therealchanger

}



void PlayerController::OnCollision(GameObject* other)
{
	if (_endOfGameTimer->IsStarted() || _deathTimer->IsStarted())return;
	//Player dies if not a coin
	StaticBoxCollider* sbc = (StaticBoxCollider*)other->getBehaviour("BOXCOLLIDER");
	if (!other->getName().find("tutorial"))
	{
		
		int num = other->getName()[other->getName().size() - 2] - '1';
		if (num > _lastTutorial)
		{
			_lastTutorial = num;
			GameStateManager::instance->_state = GameStateManager::GameState(GameStateManager::Tutorial1 + num);
		}
	}
	else if (!other->getName().find("endoflevel"))
	{
		_lockControls = true;
		lastLevelFinalScore = _coins;
		glm::vec3 camPos = AbstractGame::instance->_world->getMainCamera()->getWorldPosition();
		AbstractGame::instance->_world->add(AbstractGame::instance->_world->getMainCamera());
		AbstractGame::instance->_world->getMainCamera()->setLocalPosition(camPos);
		AbstractGame::instance->_world->addBehaviour((AbstractBehaviour*)_endOfGameTimer);
		_endOfGameTimer->Start();

	}
	else if (!other->getName().find("coin"))
	{
		other->DisableBehaviours(); //Also turns it invisible
		// particles
		_coins += 10;
		AudioManager::instance->PlaySound(4);
	}
	else if (!other->getName().find("turkeycage"))
	{
		other->DisableBehaviours();
		_coins += 100;
		AudioManager::instance->PlaySound(4);
	}
	else if (!_isBackSwitching && _isSwitching && !_isStruggling) //When In the middle of switching
	{
		_struggleTime = 0;
		_isStruggling = true;
		AudioManager::instance->PlaySound(3);
		ShakeCamera(0.2f, 0.2f);
		int lane = _nextLane;
		_nextLane = _currentLane;
		_currentLane = lane;
		_curSwitchTime = _switchTime - _curSwitchTime;
		_isBackSwitching = true;
	}
	else if (_isBackSwitching) return;
	else if (sbc->GetDimensions().y < 1.1f && !_isStruggling && lastStruggleCollider != other->getName()) //<--- This right here
	{
		AudioManager::instance->PlaySound(2);
		lastStruggleCollider = other->getName();
		Debug::Log("StartStruggle", ALL);
		//other->DisableBehaviours();
		ShakeCamera(0.2f, 0.2f);
		_isStruggling = true;
		AudioManager::instance->PlaySound(3);
		_struggleTime = 0;

		return;
	}
	else if (lastStruggleCollider == other->getName())return; //Dont trip twice over the same container
	else
	{
		AudioManager::instance->PlaySound(2);
		glm::vec3 camPos = AbstractGame::instance->_world->getMainCamera()->getWorldPosition();
		AbstractGame::instance->_world->add(AbstractGame::instance->_world->getMainCamera());
		AbstractGame::instance->_world->getMainCamera()->setLocalPosition(camPos);
		//AbstractGame::instance->SetTimeScale(5);
		_lockControls = true;
		_deathParticle->Stop(true);
		AbstractGame::instance->_world->addBehaviour((AbstractBehaviour*)_deathTimer);
		_deathParticle->Start();
		_deathTimer->Reset(true);
		AudioManager::instance->PlaySound(1);
	}
}




void PlayerController::update(float pTime)
{
	if (_isStruggling)
	{
		if (!gStruggleAnimation->IsEnabled())gStruggleAnimation->EnableBehaviours();
		_struggleTime += pTime;

		if (_struggleTime > _struggleMaxTime)
		{
			gStruggleAnimation->DisableBehaviours();

			_isStruggling = false;
		}
	}
	glm::vec3 curr = MapGenerator::instance->GetLaneAt(_currentLane)->GetPosition();
	glm::vec3 nextL;
	if (_nextLane == -1)
	{
		nextL = MapGenerator::instance->GetLaneAt(_currentLane)->GetPosition();
	}
	else
	{
		nextL = MapGenerator::instance->GetLaneAt(_nextLane)->GetPosition();
	}



	if (!_lockControls && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (_isWPRessed == false)
		{
			_isWPRessed = true;
			jump();
		}
	}
	else
	{
		_isWPRessed = false;
	}


	if (!_lockControls && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (_isAPressed == false)
		{
			switchLeft();
			_isAPressed = true;
		}
	}
	else
	{
		_isAPressed = false;
	}

	if (!_lockControls && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (_isDPressed == false)
		{
			switchRight();
			_isDPressed = true;
		}
	}
	else
	{
		_isDPressed = false;
	}

	if (_lockControls || !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (_grounded == false)
		{
			_isGoingDown = true;
		}
	}


	//if jumpButton
	//jump()

	//if left
	//switchLeft()
	//if right
	//switchRight()

	handleJump(pTime);
	handleSwitch(pTime);
	Animate(pTime);
	UpdateCamera(pTime);


}

void PlayerController::jump()
{
	if (!_grounded || _isJumping)return;
	AudioManager::instance->PlaySound(6);
	_isJumping = true;
	_grounded = false;
	_velocity = _jumpForce;

}

void PlayerController::switchLeft()
{
	if (_isSwitching)return;
	_nextLane = MapGenerator::instance->GetLaneAt(_currentLane)->GetLeft();
	if (_nextLane == -1 || _nextLane == 0)
	{
		return; //Something went wrong. u are already on most left lane? or the next lane has not yet started?
	}
	_isSwitching = true;
	_curSwitchTime = 0;
}

void PlayerController::switchRight()
{
	if (_isSwitching)return;
	_nextLane = MapGenerator::instance->GetLaneAt(_currentLane)->GetRight();
	if (_nextLane == -1 || _nextLane == MapGenerator::instance->GetNumberOfLanes() - 1)
	{
		return; //Something went wrong. u are already on most right lane? or the next lane has not yet started?
	}
	_isSwitching = true;
	_curSwitchTime = 0;
}

void PlayerController::handleSwitch(float pTime)
{
	if (_isSwitching)
	{
		float t = glm::clamp(_curSwitchTime / _switchTime, 0.f, 1.f);
		glm::vec3 oldLane, newLane;

		oldLane = MapGenerator::instance->GetLaneAt(_currentLane)->GetPosition();
		newLane = MapGenerator::instance->GetLaneAt(_nextLane)->GetPosition();
		float newX = oldLane.x + t * (newLane.x - oldLane.x);
		glm::vec3 ownerPos = _owner->getLocalPosition();
		ownerPos.x = newX;
		_owner->setLocalPosition(ownerPos);//Using smooth step to change between lanes

		_curSwitchTime += pTime;
		if (_curSwitchTime >= _switchTime)
		{
			_isSwitching = false;
			if (_isBackSwitching)
			{
				_isBackSwitching = false;
			}
			_currentLane = _nextLane;
			//Set the position of the player to the lane diectly to avoid unpresicion
			glm::vec3 posWithOwnerY = newLane;
			posWithOwnerY.y = ownerPos.y;
			_owner->setLocalPosition(posWithOwnerY);
		}

	}
}

void PlayerController::handleJump(float pTime)
{

	float tempLaneYPosition = 0; //MapGenerator::instance->GetLanePos(_currentLane).y;
	//
	//MapGenerator can be dependent on Total Time.
	//Map generator automatically returns the lane struct (interpolated) of the current position
	if (_isJumping)
	{
		if (_isGoingDown == false)
		{
			_velocity += _gravity * pTime;
		}
		else
		{
			_velocity += _gravityWhenGoingDown * pTime;
		}

		if (_owner->getLocalPosition().y + _velocity < tempLaneYPosition) //Player is on ground again
		{
			_grounded = true;
			_isJumping = false;
			_isGoingDown = false;
			_velocity = 0;
			_owner->setLocalPosition(MapGenerator::instance->GetLaneAt(_currentLane)->GetPosition());
		}
		//Add the Velocity
		if (_isJumping)_owner->setLocalPosition(_owner->getLocalPosition() + glm::vec3(0, 1, 0) * _velocity);
	}
}

void PlayerController::createModels()
{
	//player models and fake pivots
	Texture* turkeyAlb = Texture::load(config::MGE_TEXTURE_PATH + "Turkey/turkeyalbedo.png", true);
	Texture* turkeyMetal = Texture::load(config::MGE_TEXTURE_PATH + "Turkey/turkeymetal.png", false);
	Texture* turkeyNormal = Texture::load(config::MGE_TEXTURE_PATH + "Turkey/turkeynormal.png", false);

	AbstractMaterial* playerTexture = new TextureMaterial(turkeyAlb, nullptr, turkeyMetal, 2, 1, 5, 2);

	Mesh * tBody = Mesh::load(config::MGE_MODEL_PATH + "Turkey/TBody.obj");
	Mesh * tHead = Mesh::load(config::MGE_MODEL_PATH + "Turkey/THead.obj");
	Mesh * tNeck = Mesh::load(config::MGE_MODEL_PATH + "Turkey/TNeck.obj");
	Mesh * tTail = Mesh::load(config::MGE_MODEL_PATH + "Turkey/TTail.obj");

	Mesh * tLeftLeg = Mesh::load(config::MGE_MODEL_PATH + "Turkey/TLeftLeg.obj");
	Mesh * tRightLeg = Mesh::load(config::MGE_MODEL_PATH + "Turkey/TRightLeg.obj");
	Mesh * tLeftWing = Mesh::load(config::MGE_MODEL_PATH + "Turkey/TLeftWing.obj");
	Mesh * tRightWing = Mesh::load(config::MGE_MODEL_PATH + "Turkey/TRightWing.obj");

	//Finn test

	/*
	Mesh * finnHouse = Mesh::load(config::MGE_MODEL_PATH + "chickenroom.obj");
	Texture* houseAlb = Texture::load(config::MGE_TEXTURE_PATH + "chickenroom_diffuse.png");
	AbstractMaterial* houseTexture = new AnimationMaterial(houseAlb, 1);
	GameObject * finnHouseObject = new GameObject("FinnTest");
	finnHouseObject->setMesh(finnHouse);
	finnHouseObject->setMaterial(houseTexture);
	finnHouseObject->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	finnHouseObject->setLocalPosition(glm::vec3(5, 0,-10));
	getOwner()->add(finnHouseObject);
	*/




	modelsContainer = new GameObject("PlayerModelsContainer");
	modelsContainer->setLocalPosition(glm::vec3(0, -1, 0));
	getOwner()->add(modelsContainer);


	gTBody = new GameObject("bodyPivot");
	modelsContainer->add(gTBody);
	GameObject * mBody = new GameObject("bodyModel");
	mBody->setMesh(tBody);
	mBody->setMaterial(playerTexture);
	gTBody->add(mBody);

	gTLeftLeg = new GameObject("leftLegPivot");
	modelsContainer->add(gTLeftLeg);
	GameObject * mLeftLeg = new GameObject("leftLegModel");
	mLeftLeg->setMesh(tLeftLeg);
	mLeftLeg->setMaterial(playerTexture);
	gTLeftLeg->add(mLeftLeg);

	gTRightLeg = new GameObject("RightLegPivot");
	modelsContainer->add(gTRightLeg);
	GameObject * mRightLeg = new GameObject("RightLegModel");
	mRightLeg->setMesh(tRightLeg);
	mRightLeg->setMaterial(playerTexture);
	gTRightLeg->add(mRightLeg);

	gTNeck = new GameObject("NeckPivot");
	modelsContainer->add(gTNeck);
	GameObject * mNeck = new GameObject("NeckModel");
	mNeck->setMesh(tNeck);
	mNeck->setMaterial(playerTexture);
	gTNeck->add(mNeck);

	gTTail = new GameObject("tailPivot");
	gTBody->add(gTTail);
	GameObject *mTail = new GameObject("TailModel");
	mTail->setMesh(tTail);
	mTail->setMaterial(playerTexture);
	gTTail->add(mTail);

	gTHead = new GameObject("headPivot");
	gTNeck->add(gTHead);
	GameObject * mHead = new GameObject("HeadModel");
	mHead->setMesh(tHead);
	mHead->setMaterial(playerTexture);
	gTHead->add(mHead);

	gTLeftWing = new GameObject("leftWingPivot");
	gTBody->add(gTLeftWing);
	GameObject * mLeftWing = new GameObject("leftWingModel");
	mLeftWing->setMesh(tLeftWing);
	mLeftWing->setMaterial(playerTexture);
	gTLeftWing->add(mLeftWing);

	gTRightWing = new GameObject("RightWingPivot");
	gTBody->add(gTRightWing);
	GameObject * mRightWing = new GameObject("RightWingModel");
	mRightWing->setMesh(tRightWing);
	mRightWing->setMaterial(playerTexture);
	gTRightWing->add(mRightWing);

}

void PlayerController::Animate(float pDeltaTime)
{
	animationTool += pDeltaTime * animationSpeed;
	heliTool += pDeltaTime * heliAnimationSpeed;
	double sinTool = (glm::sin(animationTool) + 1) / 2;
	double sinForHeli = (glm::sin(heliTool) + 1) / 2;

	heli->setLocalPosition(heliInitialPosition + glm::vec3(sinForHeli * 4 - 2, ((glm::cos(heliTool) + 1) / 2) * 10 - 5, 0));


	modelsContainer->setTransform(glm::translate(glm::mat4x4(1), glm::vec3(0, -1, 0)));
	if (_grounded == false)
	{
		glm::mat4 m = glm::rotate(_velocity, glm::vec3(1, 0, 0));
		modelsContainer->setTransform(modelsContainer->getTransform() * m);

		glm::vec3 yPosInAir(0, 0, 0);

		yPosInAir.y = glm::clamp(getOwner()->getLocalPosition().y / maxYToJump, 0.0f, 1.0f);
		gTNeck->setLocalPosition(glm::vec3(0, -(yPosInAir.y * 0.3f), 0));
		gTLeftWing->setLocalPosition(glm::vec3(0, yPosInAir.y *0.2f, 0));
		gTRightWing->setLocalPosition(glm::vec3(0, yPosInAir.y *0.2f, 0));
		//gTTail->setLocalPosition(glm::vec3(0, -(yPosInAir.y * 0.1f), 0));
		yPosInAir.y *= 0.5f;
		gTLeftLeg->setLocalPosition(yPosInAir);
		gTRightLeg->setLocalPosition(yPosInAir);
		gTBody->setLocalPosition(glm::vec3(0, 0, 0));

		return;
	}


	gTTail->setLocalPosition(glm::vec3(0, 0, 0));
	gTLeftWing->setLocalPosition(glm::vec3(0, 0, 0));
	gTRightWing->setLocalPosition(glm::vec3(0, 0, 0));
	gTNeck->setLocalPosition(glm::vec3(0, 0, -sinTool * 0.1f));
	gTBody->setLocalPosition(glm::vec3(sinTool*0.1f - 0.05f, 0, 0));
	gTLeftLeg->setLocalPosition(glm::vec3(0, sinTool * 0.1f, 0));
	gTRightLeg->setLocalPosition(glm::vec3(0, 0.1f - sinTool * 0.1f, 0));

	currentStepTime = sinTool;

	if (_lockControls == false)
	{

		
		if (stepCheckDown == false)
		{
			if (currentStepTime - lastStepTime <= 0)
			{
				stepCheckDown = true;
				AudioManager::instance->PlayFootStep();
			}
		}
		else
		{
			if (currentStepTime - lastStepTime >= 0)
			{
				stepCheckDown = false;
				AudioManager::instance->PlayFootStep();
			}
		}

			lastStepTime = currentStepTime;
	}
}

void PlayerController::UpdateCamera(float pDeltaTime)
{

	if (timeLeftToShakeCamera > 0)
	{
		timeLeftToShakeCamera -= pDeltaTime;
	}

	if (_lockControls == true)
	{
		return;
	}

	AbstractGame::instance->_world->getMainCamera()->setLocalPosition(glm::vec3(0, 5, 8));

	if (timeLeftToShakeCamera > 0)
	{

		int fakeFloat = (int)(cameraShakeIntensity * 1000);

		float randomNumber = (float)(rand() % fakeFloat - fakeFloat / 2) / 1000.0f;
		AbstractGame::instance->_world->getMainCamera()->setLocalPosition(glm::vec3(0 + randomNumber, 5 + randomNumber, 8));

	}
}

void PlayerController::ShakeCamera(float pTime, float pIntensity)
{
	timeLeftToShakeCamera = pTime;
	cameraShakeIntensity = pIntensity;
}