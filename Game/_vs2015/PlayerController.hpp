#ifndef PLAYERCONTROLLER_HPP
#define PLAYERCONTROLLER_HPP
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "DynamicBoxCollider.hpp"

class PlayerController : public AbstractBehaviour
{
public:
	PlayerController();
	virtual ~PlayerController();
	virtual void update(float pTime) override;
	virtual void OnCollision(GameObject* other) override;
	virtual AbstractBehaviour* Clone() override;

private:
	int _currentLane;
	int _nextLane;
	float _switchTime;
	float _curSwitchTime;
	float _jumpForce;
	float _gravity;
	float _velocity;
	bool _grounded;
	bool _isJumping;
	bool _isSwitching;
	

	void jump();
	void switchLeft();
	void switchRight();
	void handleJump(float pTime);
	void handleSwitch(float pTime);

};

#endif // !PLAYERCONTROLLER_HPP
