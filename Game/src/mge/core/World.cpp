#include <iostream>
#include <algorithm>

#include "mge/core/World.hpp"
#include "mge/core/Light.hpp"
#include "../_vs2015/MapBuilder.h"
#include "mge/materials/TextureMaterial.hpp"
#include "../_vs2015/Debug.h"
World::World() :GameObject("root"), _mainCamera(0)
{
	_world = this;
	_mb = new MapBuilder(75, 15);
}

void World::setMainCamera(Camera* pCamera) {
	if (pCamera != NULL) _mainCamera = pCamera;
}

Camera* World::getMainCamera() {
	return _mainCamera;
}


void World::registerLight(Light* pLight) {
	Debug::Log("Registering light " + pLight->getName());
	_lights.push_back(pLight);
}

void World::unregisterLight(Light* pLight) {
	Debug::Log("Unregistering light " + pLight->getName());
	if (_lights.size() == 0) return;
	_lights.erase(std::remove(_lights.begin(), _lights.end(), pLight), _lights.end());
}

Light* World::getLightAt(int pIndex) {
	return _lights[pIndex];
}

int World::getLightCount() {
	return _lights.size();
}

void World::update(float pTime)
{
	GameObject::update(pTime);
	_mb->Update(pTime);
}
