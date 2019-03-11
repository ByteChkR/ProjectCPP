#include "WinScreen.h"
#include "MenuButton.h"
#include "GameStateManager.h"
#include "PlayerController.hpp"
#include "mge\util\ScoreManager.h"
#include "SaveScoreButton.h"
#include "ScoreBoardButton.h"

WinScreen::WinScreen(sf::RenderWindow *aWindow) {
	_window = aWindow;

	_background = new HudSprite("tempMenu.png");
	_nameBox = new HudSprite("HudBox.png",1.05f);
	_sendScoreBox = new HudSprite("HudBox.png", 1.05f);
	_sendScoreButton = new SaveScoreButton(_window, _sendScoreBox->sprite,this);
	_menuText = new HudText();
	_winText = new HudText();
	_name = new HudText();
	_kLogger = new KeyLogger();
	sendScore = false;
	_nameString = "Gobble";
	_name->_text.setString(_nameString);

	OrganizePanel();
}

void WinScreen::SendScore() {
	if (!sendScore && _nameString.size() > 0)
	{
		ScoreManager::instance->AddScore(PlayerController::instance->GetCoinCount(), _nameString);
		sendScore = true;
	}
	else if (!sendScore) {
		ScoreManager::instance->AddScore(PlayerController::instance->GetCoinCount(), "Gobble");
		sendScore = true;
	}
}

void WinScreen::ResetScoreSendBool() 
{
	if (sendScore) sendScore = false;
}

void WinScreen::TypeName() 
{
	std::string output;
	if (_name->_text.getString().getSize() < 11 && _kLogger->SFKey2String(&output)) {
		_nameString = _nameString + output;
		_name->_text.setString(_nameString);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
		if (_backSpace && _name->_text.getString().getSize() > 0) 
		{ 
			_name->_text.setString(_nameString.erase(_name->_text.getString().getSize()-1)); 
			_nameString = _name->_text.getString();
			_backSpace = false;
		}
	}
	else _backSpace = true;
}

void WinScreen::OrganizePanel() {
	_background->sprite.setPosition(_background->sprite.getTexture()->getSize().x / 2.0f, _background->sprite.getTexture()->getSize().y / 2.0f);

	_menuText->_text.setString("Go to Scoreboard");

	_sendScoreBox->sprite.setPosition(300, 100);
	_sendScoreBox->scaledSprite.setPosition(_sendScoreBox->sprite.getPosition());
	_sendScoreButton->SetPosition(_sendScoreBox->sprite.getPosition());
	_menuText->_text.setPosition(_sendScoreBox->sprite.getPosition());

	_nameBox->sprite.setPosition(300,200);
	_nameBox->scaledSprite.setPosition(_nameBox->sprite.getPosition());
	_name->_text.setPosition(_nameBox->sprite.getPosition().x - 15, _nameBox->sprite.getPosition().y);

	_winText->_text.setString("YOU WIN");
	_winText->_text.setPosition(300,300);
}

void WinScreen::Update() {
	draw();
	TypeName();
	_sendScoreButton->Update();
}

void WinScreen::draw() {
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_background->sprite);
	if(_sendScoreButton->scaled) _window->draw(_sendScoreBox->scaledSprite);
	else _window->draw(_sendScoreBox->sprite);

	_window->draw(_menuText->_text);
	_window->draw(_nameBox->sprite);
	_window->draw(_name->_text);

	_window->draw(_winText->_text);

	_window->popGLStates();
}

