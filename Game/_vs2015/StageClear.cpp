#include "../_vs2015/RetryButton.h"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "StageClear.h"
#include "NextStageButton.h"
#include "MenuButton.h"
#include "GL/glew.h"

StageClear::StageClear(sf::RenderWindow *aWindow) {

	_window = aWindow;
	_background = new HudSprite("tmpLoading.png");
	_clearBox = new HudSprite("level_complete_nobuttons.png");

	_nextStageButtonBox = new HudSprite("next_level_button.png", 1.05f);
	_nextStageButton = new NextStageButton(_window, _nextStageButtonBox->sprite);

	_menuButtonBox = new HudSprite("menu_button.png", 1.05f);
	_menuButton = new MenuButton(_window, _menuButtonBox->sprite);

	OrganizeScreen();
}

void StageClear::OrganizeScreen() {
	_background->sprite.setPosition(_background->sprite.getTexture()->getSize().x / 2, _background->sprite.getTexture()->getSize().y / 2);
	_clearBox->sprite.setPosition(_background->sprite.getPosition());

	_nextStageButtonBox->sprite.setPosition(_clearBox->sprite.getPosition().x, _clearBox->sprite.getPosition().y + 20);
	_nextStageButtonBox->scaledSprite.setPosition(_nextStageButtonBox->sprite.getPosition());
	_nextStageButton->SetPosition(_nextStageButtonBox->sprite.getPosition());

	_menuButtonBox->sprite.setPosition(_clearBox->sprite.getPosition().x, _clearBox->sprite.getPosition().y + 120);
	_menuButtonBox->scaledSprite.setPosition(_menuButtonBox->sprite.getPosition());
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
	_window->draw(_clearBox->sprite);
	if (_nextStageButton->scaled) _window->draw(_nextStageButtonBox->scaledSprite);
	else _window->draw(_nextStageButtonBox->sprite);

	if (_menuButton->scaled) _window->draw(_menuButtonBox->scaledSprite);
	else _window->draw(_menuButtonBox->sprite);

	_window->popGLStates();
}