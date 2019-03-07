#ifndef DataManager_HPP

#define DataManager_HPP

#include "mge/util/DataManager.h"
#include "mge/core/GameObject.hpp"
#include <vector>
#include "../_vs2015/PresetHandler.hpp"

class GameObject;

class DataManager
{
public:

	static DataManager * instance;
	DataManager();
	~DataManager();

	void SetPlayer(GameObject * pPlayer);
	void SetBackground(GameObject * pBackground);
	void SetGround(GameObject * pGround);

	GameObject * GetPlayer();
	GameObject * GetBackground();
	GameObject * GetGround();

private:
	GameObject * _playerGO;
	GameObject * _backgroundGO;
	GameObject * _groundGO;
};

#endif // !DataManager_HPP
