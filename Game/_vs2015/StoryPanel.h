#ifndef STORYPANEL_H
#define STORYPANEL_H

#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "Button.h"

class StoryPanel
{
	public:
		StoryPanel(sf::RenderWindow *aWindow);
		StoryPanel();

		void NextPanel();
		void PreviousPanel();
		void NextStoryPart();
		void Reset();
		void Update();
	private:
		void draw();
		void OrganizePanel();

		sf::RenderWindow *_window;
		HudSprite *_currentPanel;
		HudSprite *_nextButtonBox;
		Button *_nextButton;
		HudSprite *_backButtonBox;
		Button *_backButton;
		HudText *_nextText;
		int _storyPart;
		int _storyParts;
		int _part;
		int _maxPart;
		bool _isResetted = false;
};
#endif
