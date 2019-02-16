#ifndef STORYPANELHANDLER_H
#define STORYPANELHANDLER_H

#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include <vector>

static class StoryPanelHandler
{
	public:
		static StoryPanelHandler *instance;
		StoryPanelHandler();

		int GetSize(int _storyPart);
		void AddPanel(HudSprite *_sprite, int _storyPart);
		HudSprite* GetPanelAt(int _storyPart, int _part);
		int GetTotalStoryParts();
	private:
		std::vector<HudSprite*> _panelsOne;
		void InitializePanels();
};

#endif