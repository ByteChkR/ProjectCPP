#ifndef GAMESTATEMANAGER_HPP
#define GAMESTATEMANAGER_HPP

#include "mge\core\World.hpp"
#include <iostream>

static class GameStateManager 
{
	public:
		GameStateManager *instance;
		GameStateManager();
		enum GameState
		{
			Menu,
			Game,
			GameOver
		};

		void Update(float pTime ,World *_world = nullptr);

	private:
		GameState _state;

};

#endif
