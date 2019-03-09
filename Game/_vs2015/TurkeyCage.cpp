#include "TurkeyCage.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/AbstractGame.hpp"
#include "FlyAway.h"
#include "mge/config.hpp"

FlyAway* TurkeyCage::turkey = nullptr;

TurkeyCage::TurkeyCage() : AbstractBehaviour("TurkeyCage")
{
	if (turkey == nullptr)
	{
		InitializeTurkey();
	}

	//ctor
}

TurkeyCage::~TurkeyCage()
{
	//dtor

}

void TurkeyCage::InitializeTurkey()
{
	//Load obj textures and so on. Add Fly away script and keep a reference as well
	GameObject* turkeyObj = new GameObject("TurkeyCageTurkey");
	turkeyObj->addBehaviour((AbstractBehaviour*)(turkey = new FlyAway()));
	turkeyObj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "placeholder.obj"));
	Texture* diffTex = Texture::load(config::MGE_TEXTURE_PATH + "Game/Shared/TurkeyTurkeyCage_diffuse.png");
	Texture* specTex = Texture::load(config::MGE_TEXTURE_PATH + "Game/Shared/TurkeyTurkeyCage_specular.png");
	turkeyObj->setMaterial(new TextureMaterial(diffTex, nullptr, specTex, 2, 1, 5, 2));
	AbstractGame::instance->_world->add(turkeyObj);
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
	turkey->Release(_owner->getWorldPosition());
	//take from obj pool
	//send flying
	//Flying Script will deactivate and reset after x seconds
}
