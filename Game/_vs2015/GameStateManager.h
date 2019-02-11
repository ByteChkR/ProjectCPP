#ifndef GAMESTATEMANAGER_HPP
#define GAMESTATEMANAGER_HPP

#include <iostream>

class GameStateManager 
{
	public:
		GameStateManager();
		enum GameState
		{
			Menu,
			Game,
			GameOver
		};

		void Update();

	private:
		GameState _state;

};

#endif
