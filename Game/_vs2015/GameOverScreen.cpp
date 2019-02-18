#include "../_vs2015/RetryButton.h"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "GameOverScreen.h"
#include "RetryButton.h"
#include "MenuButton.h"
#include "GL/glew.h"

GameOverScreen::GameOverScreen(sf::RenderWindow *aWindow){
	
	_window = aWindow;
	_background = new HudSprite("tmpPanel0.png");

	_retryButtonBox = new HudSprite("HudBox.png",0.8f);
	_retryText = new HudText();
	_retryButton = new RetryButton(_window, _retryButtonBox->sprite);

	_menuButtonBox = new HudSprite("HudBox.png",0.8f);
	_menuText = new HudText();
	_menuButton = new MenuButton(_window, _menuButtonBox->sprite);

	OrganizeScreen();
}

void GameOverScreen::OrganizeScreen(){
	_background->sprite.setPosition(_background->sprite.getTexture()->getSize().x / 2, _background->sprite.getTexture()->getSize().y / 2);

	_retryText->_text.setString("Retry");
	_retryButtonBox->sprite.setPosition(300, 200);
	_retryButtonBox->scaledSprite.setPosition(_retryButtonBox->sprite.getPosition());
	_retryButton->SetPosition(_retryButtonBox->sprite.getPosition());
	_retryText->_text.setPosition(_retryButtonBox->sprite.getPosition());

	_menuText->_text.setString("Menu");
	_menuButtonBox->sprite.setPosition(100, 200);
	_menuButtonBox->scaledSprite.setPosition(_menuButtonBox->sprite.getPosition());
	_menuText->_text.setPosition(_menuButtonBox->sprite.getPosition());
	_menuButton->SetPosition(_menuButtonBox->sprite.getPosition());
}

void GameOverScreen::Update() {
	draw();
	_retryButton->Update();
	_menuButton->Update();
}

void GameOverScreen::draw() {
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_background->sprite);
	if (_retryButton->scaled) _window->draw(_retryButtonBox->scaledSprite);
	else _window->draw(_retryButtonBox->sprite);
	_window->draw(_retryText->_text);

	if (_menuButton->scaled)_window->draw(_menuButtonBox->scaledSprite);
	else _window->draw(_menuButtonBox->sprite);
	_window->draw(_menuText->_text);

	_window->popGLStates();
}