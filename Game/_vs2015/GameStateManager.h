#ifndef GAMESTATEMANAGER_HPP
#define GAMESTATEMANAGER_HPP

#include "mge\core\World.hpp"
#include <iostream>

static class GameStateManager 
{
	public:
		static GameStateManager *instance;
		GameStateManager();
		enum GameState
		{
			Menu,
			Game,
			GameOver
		};

		GameState _state;
		void Update(float pTime ,World *_world = nullptr);

	private:

};

#endif
