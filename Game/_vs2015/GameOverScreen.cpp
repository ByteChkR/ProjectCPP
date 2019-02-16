#include "../_vs2015/RetryButton.h"
#include "SFML\Graphics.hpp"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h""
#include "GameOverScreen.h"
#include "RetryButton.h"
#include "../include/GL/glew.h"

GameOverScreen::GameOverScreen(sf::RenderWindow *aWindow){
	_background = new HudSprite("tmpPanel0.png");
	_retryButtonBox = new HudSprite("HudBox.png");
	_retryText = new HudText();
	_retryButton = new RetryButton(_window, _retryButtonBox->sprite);

	OrganizeScreen();
}

void GameOverScreen::OrganizeScreen(){
	_retryText->_text.setString("Retry");
}

void GameOverScreen::Update() {
	draw();
	_retryButton->Update();
}

void GameOverScreen::draw() {
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_background->sprite);
	_window->draw(_retryButtonBox->sprite);
	_window->draw(_retryText->_text);

	_window->popGLStates();
}