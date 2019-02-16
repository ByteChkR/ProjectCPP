#include "../_vs2015/RetryButton.h"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h""
#include "GameOverScreen.h"
#include "RetryButton.h"
#include "MenuButton.h"
#include "GL/glew.h"

GameOverScreen::GameOverScreen(sf::RenderWindow *aWindow){
	
	_window = aWindow;
	_background = new HudSprite("tmpPanel0.png");

	_retryButtonBox = new HudSprite("HudBox.png");
	_retryText = new HudText();
	_retryButton = new RetryButton(_window, _retryButtonBox->sprite);

	_menuButtonBox = new HudSprite("HudBox.png");
	_menuText = new HudText();
	_menuButton = new MenuButton(_window, _menuButtonBox->sprite);

	OrganizeScreen();
}

void GameOverScreen::OrganizeScreen(){
	_retryText->_text.setString("Retry");
	_retryButtonBox->sprite.setPosition(200, 200);
	_retryButton->SetPosition(200, 200);
	_retryText->_text.setPosition(200, 200);

	_menuText->_text.setString("Menu");
	_menuButtonBox->sprite.setPosition(0, 200);
	_menuText->_text.setPosition(0, 200);
	_menuButton->SetPosition(0, 200);
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
	_window->draw(_retryButtonBox->sprite);
	_window->draw(_retryText->_text);

	_window->draw(_menuButtonBox->sprite);
	_window->draw(_menuText->_text);

	_window->popGLStates();
}