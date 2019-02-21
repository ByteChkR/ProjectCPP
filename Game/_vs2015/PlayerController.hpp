#ifndef PLAYERCONTROLLER_HPP
#define PLAYERCONTROLLER_HPP
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "DynamicBoxCollider.hpp"
#include "Timer.h"
#include <iostream>

class PlayerController : public AbstractBehaviour
{
public:
	PlayerController();
	virtual ~PlayerController();
	virtual void update(float pTime) override;
	virtual void OnCollision(GameObject* other) override;
	virtual AbstractBehaviour* Clone() override;
	static PlayerController* instance;
	int GetCoinCount();
	void SetCurrentLane(int lane);
private:
	Timer* _endOfGameTimer;
	int _currentLane;
	int _nextLane;
	float _switchTime;
	float _curSwitchTime;
	float _jumpForce;
	float _gravity;
	float _gravityWhenGoingDown;
	float _gravityIncreaseWhenGoingDown;
	float _velocity;
	int _coins;
	bool _isGoingDown;
	bool _grounded;
	bool _isJumping;
	bool _isSwitching;
	bool _isAPressed;
	bool _isDPressed;
	bool _isWPRessed;
	bool _isBackSwitching;
	
	void OnGameEnd();
	void OnGameEndTick(float time);

	void jump();
	void switchLeft();
	void switchRight();
	void handleJump(float pTime);
	void handleSwitch(float pTime);

};

#endif // !PLAYERCONTROLLER_HPP
