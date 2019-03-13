#include "../_vs2015/RetryButton.h"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "GameOverScreen.h"
#include "RetryButton.h"
#include "MenuButton.h"
#include "GL/glew.h"
#include "PlayerController.hpp"

GameOverScreen::GameOverScreen(sf::RenderWindow *aWindow){
	
	_window = aWindow;
	_background = new HudSprite("game over background.png");
	_GameOverBox = new HudSprite("game_over_nobuttons.png");

	_retryButtonBox = new HudSprite("try_again_button.png",1.05f);
	_retryButton = new RetryButton(_window, _retryButtonBox->sprite);

	_menuButtonBox = new HudSprite("menu_button.png",1.05f);
	_menuButton = new MenuButton(_window, _menuButtonBox->sprite);

	_progressionBox = new HudSprite("empty_window.png");

	_progressText = new HudText("Candy Beans.otf",22,sf::Color::Black);
	_scoreText = new HudText("Candy Beans.otf", 22, sf::Color::Black);

	OrganizeScreen();
}

void GameOverScreen::SetProgressAchieved(float pProgress) {
	_progress = pProgress * 100;
	_progressText->_text.setString("Level progress: " + std::to_string(_progress) + "%");
}

void GameOverScreen::OrganizeScreen(){
	_background->sprite.setPosition(_background->sprite.getTexture()->getSize().x / 2, _background->sprite.getTexture()->getSize().y / 2);
	_GameOverBox->sprite.setPosition(_background->sprite.getPosition());

	_progressionBox->sprite.setPosition(_background->sprite.getTexture()->getSize().x / 2, 175);
	_progressText->_text.setPosition(_progressionBox->sprite.getPosition().x + 50,_progressionBox->sprite.getPosition().y);
	_scoreText->_text.setPosition(_progressionBox->sprite.getPosition().x - 150, _progressionBox->sprite.getPosition().y);

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
	_score = PlayerController::instance->GetDeathCoinCount();
	_scoreText->_text.setString("Score: " + std::to_string(_score));
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

	_window->draw(_progressionBox->sprite);

	_window->draw(_progressText->_text);
	_window->draw(_scoreText->_text);

	_window->popGLStates();
}