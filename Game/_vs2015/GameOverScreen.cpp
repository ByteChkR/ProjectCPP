#include "../_vs2015/RetryButton.h"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "GameOverScreen.h"
#include "RetryButton.h"
#include "MenuButton.h"
#include "GL/glew.h"

GameOverScreen::GameOverScreen(sf::RenderWindow *aWindow){
	
	_window = aWindow;
	_background = new HudSprite("game over background.png");
	_GameOverBox = new HudSprite("game_over_nobuttons.png");

	_retryButtonBox = new HudSprite("try_again_button.png",1.05f);
	_retryButton = new RetryButton(_window, _retryButtonBox->sprite);

	_menuButtonBox = new HudSprite("menu_button.png",1.05f);
	_menuButton = new MenuButton(_window, _menuButtonBox->sprite);

	OrganizeScreen();
}

void GameOverScreen::OrganizeScreen(){
	_background->sprite.setPosition(_background->sprite.getTexture()->getSize().x / 2, _background->sprite.getTexture()->getSize().y / 2);
	_GameOverBox->sprite.setPosition(_background->sprite.getPosition());

	_retryButtonBox->sprite.setPosition(_GameOverBox->sprite.getPosition().x, _GameOverBox->sprite.getPosition().y +20);
	_retryButtonBox->scaledSprite.setPosition(_retryButtonBox->sprite.getPosition());
	_retryButton->SetPosition(_retryButtonBox->sprite.getPosition());

	_menuButtonBox->sprite.setPosition(_GameOverBox->sprite.getPosition().x, _GameOverBox->sprite.getPosition().y + 120);
	_menuButtonBox->scaledSprite.setPosition(_menuButtonBox->sprite.getPosition());
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
	_window->draw(_GameOverBox->sprite);
	if (_retryButton->scaled) _window->draw(_retryButtonBox->scaledSprite);
	else _window->draw(_retryButtonBox->sprite);

	if (_menuButton->scaled)_window->draw(_menuButtonBox->scaledSprite);
	else _window->draw(_menuButtonBox->sprite);

	_window->popGLStates();
}