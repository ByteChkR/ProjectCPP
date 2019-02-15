#include "mge/util/DataManager.h"

#include <iostream>
#include "..\_vs2015\ScriptableLuaObject.h"
#include "..\_vs2015\LuaOperations.h"

 DataManager * DataManager::instance;

DataManager:: DataManager()
{
	instance = this;
}
DataManager::~DataManager()
{
	instance = nullptr;
}



void DataManager::SetPlayer(GameObject * pPlayer)
{
	_playerGO = pPlayer;
}

void DataManager::SetBackground(GameObject * pBackground)
{
	_backgroundGO = pBackground;
}

void DataManager::SetGround(GameObject * pGround)
{
	_groundGO = pGround;
}



GameObject * DataManager::GetPlayer()
{
	return _playerGO;
}

GameObject * DataManager::GetBackground()
{
	return _backgroundGO;
}

GameObject * DataManager::GetGround()
{
	return _groundGO;
}


