#include "StoryPanel.h"
#include "StoryPanelHandler.h"
#include "NextButton.h"
#include "GameStateManager.h"

StoryPanel::StoryPanel(sf::RenderWindow *aWindow)
{
	_storyPart = 0;
	_part = 0;
	_storyParts = StoryPanelHandler::instance->GetTotalStoryParts();
	_window = aWindow;
	_maxPart = StoryPanelHandler::instance->GetSize(_storyPart);
	_currentPanel = StoryPanelHandler::instance->GetPanelAt(_storyPart,_part);
	_nextButtonBox = new HudSprite("HudBox.png");
	_nextText = new HudText();
	_nextButton = new NextButton(_window, _nextButtonBox->sprite, this);
	OrganizePanel();
}

StoryPanel::StoryPanel(){}

void StoryPanel::OrganizePanel()
{
	_nextText->_text.setString("Next");
}

void StoryPanel::NextPanel()
{
	if (_part < _maxPart - 1) { 
		++_part; 
		_currentPanel = StoryPanelHandler::instance->GetPanelAt(_storyPart, _part);
	}
	else {
		GameStateManager::instance->_state = GameStateManager::StateGame;
		NextStoryPart();
	}
}
void StoryPanel::NextStoryPart()
{
	if (_storyPart < _storyParts) {
		++_storyPart;
	}
	_part = 0;
}

void StoryPanel::Reset() {
	if (!_isResetted) {
		_storyPart = 0;
		_part = 0;
		_currentPanel = StoryPanelHandler::instance->GetPanelAt(_storyPart, _part);
		_isResetted = true;
	}
}

void StoryPanel::Update()
{
	if (_isResetted) _isResetted = false;
	_nextButton->Update();
	draw();
}

void StoryPanel::draw() {
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_currentPanel->sprite);
	_window->draw(_nextButtonBox->sprite);
	_window->draw(_nextText->_text);

	_window->popGLStates();
}