#ifndef GAMESTATEMANAGER_HPP
#define GAMESTATEMANAGER_HPP

#include "mge\core\World.hpp"
#include <iostream>
#include"../_vs2015/Menu.h"

class GameStateManager 
{
	public:
		static GameStateManager *instance;

		enum GameState
		{
			StateMenu,
			StatePanel,
			StateGame,
			StateGameOver,
			StateNextStage,
			StateWin
		};


		GameStateManager(GameState initialState = GameState::StateMenu);

		GameState _state;
		void Update(float pTime ,World *_world = nullptr);

	private:
		Menu *_menu;
};

#endif
