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

		int _initFrame = 0;

        void _updateHud();
        MGEDemo(const MGEDemo&);
        MGEDemo& operator=(const MGEDemo&);
};

#endif // MGEDEMO_HPP
