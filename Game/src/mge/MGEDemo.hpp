#ifndef MGEDEMO_HPP
#define MGEDEMO_HPP

#include "mge/core/AbstractGame.hpp"
#include "../_vs2015/MapBuilder.h"
#include"../_vs2015/Menu.h"
#include "../_vs2015/StoryPanel.h"
#include "../_vs2015/GameOverScreen.h"

class DebugHud;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class MGEDemo: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		MGEDemo();
		virtual ~MGEDemo();

        //override initialize so we can add a DebugHud
        virtual void initialize();

	protected:
	    //override so we can construct the actual scene
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render(int pass) override;

	private:
		DebugHud* _hud;                   //hud display
		Menu* _menu;
		StoryPanel* _storyPanel;
		GameOverScreen* _gameOverScreen;

        void _updateHud();
        MGEDemo(const MGEDemo&);
        MGEDemo& operator=(const MGEDemo&);
};

#endif // MGEDEMO_HPP
