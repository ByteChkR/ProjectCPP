#ifndef CAR_HPP

#define CAR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"
#include "StaticBoxCollider.hpp"

class Car : public AbstractBehaviour
{
public:
	Car(bool blueprint = false);
	virtual ~Car();
	virtual void update(float pStep) override;
	virtual AbstractBehaviour* Clone() override;
	virtual void enable() override;
	virtual void disable() override;
private:
	float _speed;
	bool _isBlueprint;
	bool _initialized;

	GameObject* _carModel;
	StaticBoxCollider* _sbc;
};

#endif
