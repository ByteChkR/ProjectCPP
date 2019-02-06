#include "PlayerController.hpp"

PlayerController::PlayerController()
{
	_currentLane = 0;
	_gravity = -1;
	_jumpForce = 0.2f;
	_velocity = 0;
	_switchTime = 0.5f;
	_curSwitchTime = 0;
	_nextLane = -1;

	_grounded = false;
	_isSwitching = false;
	_isJumping = true;
	
}

PlayerController::~PlayerController()
{

}

void PlayerController::OnCollision(GameObject* other)
{
	//Player dies if not a coin
}

void PlayerController::update(float pTime)
{
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
	_velocity = _jumpForce;

}

void PlayerController::switchLeft()
{
	if (_isSwitching)return;
	_nextLane = 1; //Temp number, replace with adjacent lane to the left(from the map generator)
	//_nextLane = MapGenerator::instance->GetLane(LEFT)
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
	_nextLane = 1; //Temp number, replace with adjacent lane to the right(from the map generator)
	//_nextLane = MapGenerator::instance->GetLane(RIGHT)
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
		oldLane = newLane = glm::vec3(0);//Temp values. will get replaced by lane position of current and next
		//oldLane = MapGenerator::instance->GetLanePos(_currentLane);
		//newLane = MapGenerator::instance->GetLanePos(_nextLane);
		_owner->setLocalPosition(glm::smoothstep(oldLane, newLane, glm::vec3(t)));//Using smooth step to change between lanes
		_curSwitchTime += pTime;
		if (_curSwitchTime >= _switchTime)
		{
			_isSwitching = false;
			_currentLane = _nextLane;
			//Set the position of the player to the lane diectly to avoid unpresicion
			//_owner.setLocalPosition(newLane);
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
		_velocity += _gravity * pTime;
		if (_owner->getLocalPosition().y + _velocity < tempLaneYPosition) //Player is on ground again
		{
			_grounded = true;
			_isJumping = false;
			_velocity = 0;
			//_owner->setLocalPosition(MapGenerator::instance->GetLanePos(_currentLane));
		}
		//Add the Velocity
		if(_isJumping)_owner->setLocalPosition(_owner->getLocalPosition() + glm::vec3(0, 1, 0) * _velocity);
	}
}