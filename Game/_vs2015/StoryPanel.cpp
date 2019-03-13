#include "StoryPanel.h"
#include "StoryPanelHandler.h"
#include "NextButton.h"
#include "GameStateManager.h"
#include "PlayerController.hpp"
#include "PanelBackButton.h"
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

	_nextButtonBox = new HudSprite("arrow_right.png",1.05f);
	_nextButton = new NextButton(_window, _nextButtonBox->sprite, this);

	_backButtonBox = new HudSprite("arrow_left.png", 1.05f);
	_backButton = new PanelBackButton(_window, _backButtonBox->sprite, this);

	OrganizePanel();
}

StoryPanel::StoryPanel(){}

void StoryPanel::OrganizePanel()
{
	_nextButtonBox->sprite.setPosition(1800,950);
	_nextButtonBox->scaledSprite.setPosition(_nextButtonBox->sprite.getPosition());
	_nextButton->SetPosition(_nextButtonBox->sprite.getPosition());

	_backButtonBox->sprite.setPosition(100, 950);
	_backButtonBox->scaledSprite.setPosition(_backButtonBox->sprite.getPosition());
	_backButton->SetPosition(_backButtonBox->sprite.getPosition());
}

void StoryPanel::NextPanel()
{
	if (_part < _maxPart - 1) { 
		++_part; 
		_currentPanel = StoryPanelHandler::instance->GetPanelAt(_storyPart, _part);
		_currentPanel->sprite.setPosition(_currentPanel->sprite.getTexture()->getSize().x / 2.0f, _currentPanel->sprite.getTexture()->getSize().y / 2.0f);
	}
	else if(_storyPart == _storyParts){
		GameStateManager::instance->_state = GameStateManager::StateWin;
	}
	else {
		GameStateManager::instance->_state = GameStateManager::StateGame;
		NextStoryPart();
	}
}

void StoryPanel::PreviousPanel() {
	if (_part > 0) {
		--_part;
		_currentPanel = StoryPanelHandler::instance->GetPanelAt(_storyPart, _part);
		_currentPanel->sprite.setPosition(_currentPanel->sprite.getTexture()->getSize().x / 2.0f, _currentPanel->sprite.getTexture()->getSize().y / 2.0f);
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
	_backButton->Update();
	draw();
}

void StoryPanel::draw() {
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_currentPanel->sprite);
	if(_nextButton->scaled)_window->draw(_nextButtonBox->scaledSprite);
	else _window->draw(_nextButtonBox->sprite);

	if (_part > 0) {
		if (_backButton->scaled)_window->draw(_backButtonBox->scaledSprite);
		else _window->draw(_backButtonBox->sprite);
	}
	_window->popGLStates();
}