#ifndef MGEDEMO_HPP
#define MGEDEMO_HPP

#include "mge/core/AbstractGame.hpp"
#include "../_vs2015/MapBuilder.h"
#include"../_vs2015/Menu.h"
#include "../_vs2015/StoryPanel.h"
#include "../_vs2015/GameOverScreen.h"
#include "../_vs2015/StageClear.h"
#include "../_vs2015/WinScreen.h"
#include "../_vs2015/LoadingScreen.h"
#include "../_vs2015/ScoreBoard.h"
#include "../_vs2015/Credits.h"
#include "../_vs2015/Tutorial0.h"
#include "../_vs2015/Tutorial1.h"
#include "../_vs2015/Tutorial2.h"
#include "../_vs2015/Tutorial3.h"

class DebugHud;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class MGEDemo: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		MGEDemo(int argc, char *argv[]);
		virtual ~MGEDemo();

        //override initialize so we can add a DebugHud
        virtual void initialize();

	protected:
	    //override so we can construct the actual scene
        virtual void _initializeScene();

		void _initializeResources();
	    //override render to render the hud as well.
	    virtual void _render(int pass) override;

	private:
		int argc;
		std::vector<std::string> argv;
		DebugHud* _hud;                   //hud display
		Menu* _menu;
		StoryPanel* _storyPanel;
		GameOverScreen* _gameOverScreen;
		StageClear* _stageClear;
		WinScreen* _winScreen;
		LoadingScreen* _loadingScreen;
		ScoreBoard* _scoreBoard;
		Credits* _credits;
		Tutorial0* _tutorial0;
		Tutorial1* _tutorial1;
		Tutorial2* _tutorial2;
		Tutorial3* _tutorial3;

		int _initFrame = 0;

        void _updateHud();
        MGEDemo(const MGEDemo&);
        MGEDemo& operator=(const MGEDemo&);
};

#endif // MGEDEMO_HPP
