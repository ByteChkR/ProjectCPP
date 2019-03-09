#include "glm.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "Car.h"
#include "mge/core/AbstractGame.hpp"
#include "Debug.h"
#include "PlayerController.hpp"
Car::Car(bool blueprint)
{
	_isBlueprint = blueprint;
	_carModel = nullptr;
	_sbc = nullptr;
	if (_isBlueprint)
	{
		_initialized = true;
	}
	else {
		_initialized = false;
	}
}

Car::~Car()
{
	AbstractBehaviour::~AbstractBehaviour();
}

void Car::disable()
{
	AbstractBehaviour::disable();

	if (!_initialized)return;
	//_owner->setLocalPosition(_initPos);
}

void Car::enable()
{
	AbstractBehaviour::enable();
	//Override to determine speed semi randomly
	_speed = 10;
	if (!_initialized)return;
	_carModel->setLocalPosition(glm::vec3(0));
	_sbc->SetOffset(glm::vec3(0));
}

AbstractBehaviour* Car::Clone()
{
	return new Car();
}

void Car::update(float pStep)
{
	if (!_initialized && _isBlueprint)
	{
		_initialized = true;
	}
	else if (!_initialized)
	{
		//Debug::Log(std::to_string(_owner->getChildCount()),ALL);
		_carModel = new	GameObject("CarModel");
		_carModel->setMaterial(_owner->getMaterial());
		_carModel->setMesh(_owner->getMesh());
		_owner->setMesh(nullptr);
		_owner->setMaterial(nullptr);
		_owner->add(_carModel);
		_initialized = true;
		_sbc = (StaticBoxCollider*)_owner->getBehaviour("BOXCOLLIDER");


		if (_carModel != nullptr && _sbc != nullptr)_initialized = true;
	}
	if (_initialized && !_isBlueprint && PlayerController::instance->IsMoving())
	{
		float speed = (_speed+_owner->getLocalPosition().x/2) * pStep;
		_carModel->translate(glm::vec3(0, 0, speed));
		_sbc->AddOffset(glm::vec3(0, 0, speed));

	}

}