#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "ScoreBoard.h"
#include "MenuButton.h"
#include "Credits.h"
#include "GL/glew.h"
#include "mge/util/ScoreManager.h"

ScoreBoard::ScoreBoard(sf::RenderWindow *aWindow) {

	_window = aWindow;
	_background = new HudSprite("scoreboard_nobutton.png");

	_menuButtonBox = new HudSprite("cancel_button.png", 1.05f);
	_menuButton = new MenuButton(_window, _menuButtonBox->sprite);
	
	_size = ScoreManager::instance->GetScores().size();

	for (int i = 0; i < 10; i++) {
		_scoreDisplays.push_back(new HudText("Scoreboard_font.ttf",30,sf::Color::Black));
		_nameDisplays.push_back(new HudText("Scoreboard_font.ttf",30,sf::Color::Black));
	}
	
	OrganizeScreen();
	UpdateScores();
}

void ScoreBoard::UpdateScores() {

	_scores = ScoreManager::instance->GetScores();
	for (int i = 0; i < _size; i++) {
		_nameDisplays[i]->_text.setString(_scores[i].name);
		_scoreDisplays[i]->_text.setString(std::to_string((int)_scores[i].value));
	}
}

void ScoreBoard::OrganizeScreen() {
	_background->sprite.setPosition((float)_background->sprite.getTexture()->getSize().x / 2.0f, _background->sprite.getTexture()->getSize().y / 2.0f);
	
	float wholeBlockOffset = 380;
	float lineOffset = 47.5f;

	for (int i = 0; i < _size; i++) {
		_nameDisplays[i]->_text.setPosition( 200 , wholeBlockOffset +lineOffset * (i + 1));
		_scoreDisplays[i]->_text.setPosition(500 , wholeBlockOffset + lineOffset * (i + 1));
	}
	
	_menuButtonBox->sprite.setPosition(_background->sprite.getPosition().x+ 302, _background->sprite.getPosition().y - 365);
	_menuButtonBox->scaledSprite.setPosition(_menuButtonBox->sprite.getPosition());
	_menuButton->SetPosition(_menuButtonBox->sprite.getPosition());
}

void ScoreBoard::Update() {
	draw();
	_menuButton->Update();
}

void ScoreBoard::draw() {
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_background->sprite);
	
	for (int i = 0; i < _size; i++) {
		_window->draw(_nameDisplays[i]->_text);
		_window->draw(_scoreDisplays[i]->_text);
	}
	
	if (_menuButton->scaled) _window->draw(_menuButtonBox->scaledSprite);
	else _window->draw(_menuButtonBox->sprite);

	_window->popGLStates();
}