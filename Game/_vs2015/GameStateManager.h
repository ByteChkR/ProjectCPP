#ifndef GAMESTATEMANAGER_HPP
#define GAMESTATEMANAGER_HPP

#include "mge\core\World.hpp"
#include <iostream>
#include"../_vs2015/Menu.h"

static class GameStateManager 
{
	public:
		static GameStateManager *instance;
		GameStateManager();
		enum GameState
		{
			StateMenu,
			StateGame,
			StateGameOver
		};

		GameState _state;
		void Update(float pTime ,World *_world = nullptr);

	private:
		Menu *_menu;
};

#endif
