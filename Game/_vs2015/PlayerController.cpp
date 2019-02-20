#include "PlayerController.hpp"
#include "SFML/Window.hpp"
#include "mge/util/MapGenerator.h"
#include "GameStateManager.h"
#include "MapBuilder.h"
#include "LevelManager.h"

PlayerController* PlayerController::instance = nullptr;

PlayerController::PlayerController()
{
	
	_currentLane = 1;
	_gravity = -1;
	_gravityWhenGoingDown = -5;
	_isBackSwitching = false;
	_jumpForce = 0.45f;
	_velocity = 0;
	_switchTime = 0.1f;
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
	instance = this;
}

AbstractBehaviour* PlayerController::Clone()
{
	return new PlayerController();
}

PlayerController::~PlayerController()
{

}

void PlayerController::SetCurrentLane(int lane)
{
	_currentLane = lane;
}


int PlayerController::GetCoinCount()
{
	return _coins;
}

void PlayerController::OnCollision(GameObject* other)
{
	//Player dies if not a coin
	std::cout << "COLLISION\n";
	if (!other->getName().find("endoflevel"))
	{
		MapBuilder::instance->Unload();
		//LevelManager::instance->NextLevel();
		GameStateManager::instance->_state = GameStateManager::StateNextStage;
		MapBuilder::instance->GetContainer()->setLocalPosition(glm::vec3(0, 0, -60));
	}
	else if (!other->getName().find("coin"))
	{
		other->DisableBehaviours(); //Also turns it invisible
		// particles
		_coins++;
	}
	else if(!_isBackSwitching && _isSwitching) //When In the middle of switching
	{
		int lane = _nextLane;
		_nextLane = _currentLane;
		_currentLane = lane;
		_curSwitchTime = _switchTime - _curSwitchTime;
		_isBackSwitching = true;
	}
	else if (_isBackSwitching)return;
	else
	{

		GameStateManager::instance->_state = GameStateManager::StateGameOver;
		MapBuilder::instance->Unload();
		MapBuilder::instance->GetContainer()->setLocalPosition(glm::vec3(0, 0, -60));
	}
}


void PlayerController::update(float pTime)
{

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



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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


}

void PlayerController::jump()
{
	if (!_grounded || _isJumping)return;
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