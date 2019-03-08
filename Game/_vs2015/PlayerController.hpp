#ifndef PLAYERCONTROLLER_HPP
#define PLAYERCONTROLLER_HPP
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "DynamicBoxCollider.hpp"
#include "mge/util/AudioManager.h"
#include "Timer.h"
#include <iostream>
#include "ParticleEmitter.h"
#include "Particle.h"




class PlayerController : public AbstractBehaviour
{
public:
	PlayerController(GameObject * pOwner, GameObject * pHeli,GameObject * pHeliDrop);
	virtual ~PlayerController();
	virtual void update(float pTime) override;
	virtual void OnCollision(GameObject* other) override;
	virtual AbstractBehaviour* Clone() override;
	static PlayerController* instance;
	int GetCoinCount();
	void SetCurrentLane(int lane);
	bool IsMoving();
	void ResetScore(int newScore = 0);
	void ResetTutorial();
	void Reset();

	bool _tutorialColliderStay;
private:
	Timer* _endOfGameTimer;
	Timer* _deathTimer;
	int _currentLane;
	int _nextLane;
	float _switchTime;
	float _curSwitchTime;
	float _jumpForce;
	float _gravity;
	float _gravityWhenHovering;
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
	bool _isStruggling;
	bool _test;
	float _struggleTime;
	float _struggleMaxTime;
	bool _lockControls;
	
	bool _godMode;

	int _lastTutorial;

	void OnGameEnd();
	void OnGameEndTick(float time);

	void OnDeathEnd();
	void OnDeathTick(float time);

	void jump();
	void switchLeft();
	void switchRight();
	void handleJump(float pTime);
	void handleSwitch(float pTime);

	void createModels();
	void Animate(float pDeltaTime);
	void UpdateCamera(float pDeltaTime);
	void ShakeCamera(float pTime, float pIntensity);

	//animation
	float cameraShakeIntensity = 1;
	float timeLeftToShakeCamera = 0;
	float animationTool = 0; // delta time addition
	float animationSpeed =20.0f;
	float maxYToJump = 40;

	//footsteps
	double lastStepTime =0;
	double currentStepTime=0;
	bool stepCheckDown = true;
	//empty game objects that serve as pivots

	bool _colstay;

	ParticleEmitter* _deathParticle;
	GameObject* _deathContainer;

	GameObject * modelsContainer;

	GameObject * gTBody;
	GameObject * gTNeck;
	GameObject * gTLeftLeg;
	GameObject * gTRightLeg;
	GameObject * gTLeftWing;
	GameObject * gTRightWing;
	GameObject * gTHead;
	GameObject * gTTail;

	GameObject* gStruggleContainer;

	// helicoper

	glm::vec3 heliInitialPosition;
	GameObject* heli;
	float heliTool=0;
	float heliAnimationSpeed = 1.0f;

	GameObject* heliDrop;
	float heliDropTool;
	float heliDropSpeed = 1.0f;

	int lastLevelFinalScore;

	std::string lastStruggleCollider;

};

#endif // !PLAYERCONTROLLER_HPP
