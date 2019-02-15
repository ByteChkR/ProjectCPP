#include "StoryPanelHandler.h"
#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"

StoryPanelHandler *StoryPanelHandler::instance;

StoryPanelHandler::StoryPanelHandler(){
	StoryPanelHandler::instance = this;
	InitializePanels();
}

void StoryPanelHandler::AddPanel(HudSprite *_sprite,int _storyPart){
	if(_storyPart == 0){
		_panelsOne.push_back(_sprite);
	}
}

HudSprite* StoryPanelHandler::GetPanelAt(int _storyPart, int _part){
	if(_storyPart == 0){
		return _panelsOne[_part];
	}
	return nullptr;
}

void StoryPanelHandler::InitializePanels(){
	_panelsOne.push_back(new HudSprite("tempMenu.png"));
	_panelsOne.push_back(new HudSprite("tmpPanel0.png"));
	_panelsOne.push_back(new HudSprite("tmpPanel1.png"));
}

int StoryPanelHandler::GetSize(int _storyPart) {
	if (_storyPart == 0) {
		return _panelsOne.size();
	}
	return 0;
}