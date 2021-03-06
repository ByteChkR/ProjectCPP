#ifndef STORYPANELHANDLER_H
#define STORYPANELHANDLER_H

#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include <vector>

class StoryPanelHandler
{
	public:
		static StoryPanelHandler *instance;
		StoryPanelHandler();

		int GetSize(int _storyPart);
		HudSprite* GetPanelAt(int _storyPart, int _part);
		int GetTotalStoryParts();
	private:
		std::vector<HudSprite*> _panelsOne;
		std::vector<HudSprite*> _panelsTwo;
		std::vector<HudSprite*> _panelsThree;
		std::vector<HudSprite*> _panelsFour;
		void InitializePanels();
};

#endif