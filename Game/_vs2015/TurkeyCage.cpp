#include "TurkeyCage.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/AbstractGame.hpp"

TurkeyCage::TurkeyCage() : AbstractBehaviour("TurkeyCage")
{

	//ctor
}

TurkeyCage::~TurkeyCage()
{
	//dtor
}

AbstractBehaviour* TurkeyCage::Clone()
{
	return new TurkeyCage();
}

void TurkeyCage::update(float pStep)
{
	
}
