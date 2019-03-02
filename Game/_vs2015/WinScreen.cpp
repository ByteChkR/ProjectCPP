#include "WinScreen.h"
#include "MenuButton.h"
#include "GameStateManager.h"

WinScreen::WinScreen(sf::RenderWindow *aWindow) {
	_window = aWindow;

	_background = new HudSprite("tempMenu.png");
	_menuButtonBox = new HudSprite("HudBox.png",0.8f);
	_menuText = new HudText();
	_menuButton = new MenuButton(_window, _menuButtonBox->sprite);
	_winText = new HudText();

	OrganizePanel();
}

void WinScreen::OrganizePanel() {
	_background->sprite.setPosition(_background->sprite.getTexture()->getSize().x / 2.0f, _background->sprite.getTexture()->getSize().y / 2.0f);

	_menuText->_text.setString("Menu");

	_menuButtonBox->sprite.setPosition(300, 100);
	_menuButton->SetPosition(_menuButtonBox->sprite.getPosition());
	_menuButtonBox->scaledSprite.setPosition(_menuButtonBox->sprite.getPosition());
	_menuText->_text.setPosition(_menuButtonBox->sprite.getPosition());

	_winText->_text.setString("YOU WIN");
	_winText->_text.setPosition(300,300);
}

void WinScreen::Update() {
	draw();
	_menuButton->Update();
}

void WinScreen::draw() {
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_background->sprite);
	if (_menuButton->scaled) _window->draw(_menuButtonBox->scaledSprite);
	else _window->draw(_menuButtonBox->sprite);
	_window->draw(_menuText->_text);

	_window->draw(_winText->_text);

	_window->popGLStates();
}

