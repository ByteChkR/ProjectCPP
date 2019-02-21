#include "../_vs2015/RetryButton.h"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "StageClear.h"
#include "NextStageButton.h"
#include "MenuButton.h"
#include "GL/glew.h"

StageClear::StageClear(sf::RenderWindow *aWindow) {

	_window = aWindow;
	_background = new HudSprite("tmpPanel0.png");

	_nextStageButtonBox = new HudSprite("HudBox.png", 0.8f);
	_nextStageText = new HudText();
	_nextStageButton = new NextStageButton(_window, _nextStageButtonBox->sprite);

	_menuButtonBox = new HudSprite("HudBox.png", 0.8f);
	_menuText = new HudText();
	_menuButton = new MenuButton(_window, _menuButtonBox->sprite);

	OrganizeScreen();
}

void StageClear::OrganizeScreen() {
	_nextStageText->_text.setString("Next Stage");
	_nextStageButtonBox->sprite.setPosition(200, 200);
	_nextStageButtonBox->scaledSprite.setPosition(_nextStageButtonBox->sprite.getPosition());
	_nextStageButton->SetPosition(_nextStageButtonBox->sprite.getPosition());
	_nextStageText->_text.setPosition(_nextStageButtonBox->sprite.getPosition());

	_menuText->_text.setString("Menu");
	_menuButtonBox->sprite.setPosition(50, 200);
	_menuButtonBox->scaledSprite.setPosition(_menuButtonBox->sprite.getPosition());
	_menuText->_text.setPosition(_menuButtonBox->sprite.getPosition());
	_menuButton->SetPosition(_menuButtonBox->sprite.getPosition());
}

void StageClear::Update() {
	draw();
	_nextStageButton->Update();
	_menuButton->Update();
}

void StageClear::draw() {
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_background->sprite);
	if (_nextStageButton->scaled) _window->draw(_nextStageButtonBox->scaledSprite);
	else _window->draw(_nextStageButtonBox->sprite);
	_window->draw(_nextStageText->_text);

	if (_menuButton->scaled) _window->draw(_menuButtonBox->scaledSprite);
	else _window->draw(_menuButtonBox->sprite);
	_window->draw(_menuText->_text);

	_window->popGLStates();
}