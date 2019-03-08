#include "TurkeyCage.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/AbstractGame.hpp"

GameObject* TurkeyCage::turkey = nullptr;

TurkeyCage::TurkeyCage() : AbstractBehaviour("TurkeyCage")
{


	//ctor
}

TurkeyCage::~TurkeyCage()
{
	//dtor
}

void TurkeyCage::InitializeTurkey()
{
	//Load obj textures and so on. Add Fly away script and keep a reference as well
}

AbstractBehaviour* TurkeyCage::Clone()
{
	return new TurkeyCage();
}


void TurkeyCage::update(float pStep)
{
	//do nothing
}
void TurkeyCage::Release()
{
	//take from obj pool
	//send flying
	//Flying Script will deactivate and reset after x seconds
}
