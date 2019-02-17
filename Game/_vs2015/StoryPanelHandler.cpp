#include "StoryPanelHandler.h"
#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"

StoryPanelHandler *StoryPanelHandler::instance;

StoryPanelHandler::StoryPanelHandler(){
	StoryPanelHandler::instance = this;
	InitializePanels();
}

int StoryPanelHandler::GetTotalStoryParts()
{
	return 1;							//starts counting from 0
}

HudSprite* StoryPanelHandler::GetPanelAt(int _storyPart, int _part){
	if(_storyPart == 0){
		return _panelsOne[_part];
	}
	else if(_storyPart == 1){
		return _panelsTwo[_part];
	}
	return nullptr;
}

void StoryPanelHandler::InitializePanels(){
	_panelsOne.push_back(new HudSprite("tempMenu.png"));
	_panelsOne.push_back(new HudSprite("tmpPanel0.png"));
	_panelsOne.push_back(new HudSprite("tmpPanel1.png"));

	_panelsTwo.push_back(new HudSprite("tmpPanel0.png"));
	_panelsTwo.push_back(new HudSprite("tempMenu.png"));
	_panelsTwo.push_back(new HudSprite("tmpPanel1.png"));
}

int StoryPanelHandler::GetSize(int _storyPart) {
	if (_storyPart == 0) {
		return _panelsOne.size();
	}
	else if(_storyPart == 1){
		return _panelsTwo.size();
	}
	return 0;
}