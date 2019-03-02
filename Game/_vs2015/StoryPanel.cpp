#include "StoryPanel.h"
#include "StoryPanelHandler.h"
#include "NextButton.h"
#include "GameStateManager.h"
#include "PlayerController.hpp"
#include "mge/util/ScoreManager.h"

StoryPanel::StoryPanel(sf::RenderWindow *aWindow)
{
	_storyPart = 0;
	_part = 0;
	_storyParts = StoryPanelHandler::instance->GetTotalStoryParts();
	_window = aWindow;
	_maxPart = StoryPanelHandler::instance->GetSize(_storyPart);
	_currentPanel = StoryPanelHandler::instance->GetPanelAt(_storyPart,_part);
	_currentPanel->sprite.setPosition(_currentPanel->sprite.getTexture()->getSize().x/2.0f, _currentPanel->sprite.getTexture()->getSize().y/2.0f);
	_nextButtonBox = new HudSprite("HudBox.png",1.05f);
	_nextText = new HudText();
	_nextButton = new NextButton(_window, _nextButtonBox->sprite, this);
	OrganizePanel();
}

StoryPanel::StoryPanel(){}

void StoryPanel::OrganizePanel()
{
	_nextButtonBox->sprite.setPosition(400,400);
	_nextButtonBox->scaledSprite.setPosition(_nextButtonBox->sprite.getPosition());
	_nextButton->SetPosition(_nextButtonBox->sprite.getPosition());
	_nextText->_text.setPosition(_nextButtonBox->sprite.getPosition());
	_nextText->_text.setString("Next");
}

void StoryPanel::NextPanel()
{
	if (_part < _maxPart - 1) { 
		++_part; 
		_currentPanel = StoryPanelHandler::instance->GetPanelAt(_storyPart, _part);
		_currentPanel->sprite.setPosition(_currentPanel->sprite.getTexture()->getSize().x / 2.0f, _currentPanel->sprite.getTexture()->getSize().y / 2.0f);
	}
	else if(_storyPart == _storyParts){
		ScoreManager::instance->AddScore((float)PlayerController::instance->GetCoinCount(),"Test Name");
		GameStateManager::instance->_state = GameStateManager::StateWin;
	}
	else {
		GameStateManager::instance->_state = GameStateManager::StateGame;
		NextStoryPart();
	}
}
void StoryPanel::NextStoryPart()
{
	_part = 0;
	if (_storyPart < _storyParts) {
		++_storyPart;
		_maxPart = StoryPanelHandler::instance->GetSize(_storyPart);
		_currentPanel = StoryPanelHandler::instance->GetPanelAt(_storyPart, _part);
		_currentPanel->sprite.setPosition(_currentPanel->sprite.getTexture()->getSize().x / 2.0f, _currentPanel->sprite.getTexture()->getSize().y / 2.0f);
	}
}

void StoryPanel::Reset() {
	if (!_isResetted) {
		_storyPart = 0;
		_part = 0;
		_maxPart = StoryPanelHandler::instance->GetSize(_storyPart);
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
	if(_nextButton->scaled)_window->draw(_nextButtonBox->scaledSprite);
	else _window->draw(_nextButtonBox->sprite);
	_window->draw(_nextText->_text);

	_window->popGLStates();
}