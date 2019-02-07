#include "PlayerController.hpp"
#include "SFML/Window.hpp"
#include "mge/util/MapGenerator.h"
#include "MapBuilder.h"
PlayerController::PlayerController()
{
	_currentLane = 0;
	_gravity = -1;
	_gravityWhenGoingDown = -5;
	_jumpForce = 0.3f;
	_velocity = 0;
	_switchTime = 0.1f;
	_curSwitchTime = 0;
	_nextLane = -1;

	_grounded = false;
	_isSwitching = false;
	_isJumping = true;
	_isGoingDown = false;
	_isAPressed = false;
	_isDPressed = false;
	_isWPRessed = false;

}

AbstractBehaviour* PlayerController::Clone()
{
	return new PlayerController();
}

PlayerController::~PlayerController()
{

}

void PlayerController::OnCollision(GameObject* other)
{
	//Player dies if not a coin
	std::cout << "COLLISION\n";

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

	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
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
	if (_nextLane == -1)
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
	if (_nextLane == -1)
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