#include "WinScreen.h"
#include "MenuButton.h"
#include "GameStateManager.h"

WinScreen::WinScreen(sf::RenderWindow *aWindow) {
	_window = aWindow;

	_background = new HudSprite("tempMenu.png");
	_menuButtonBox = new HudSprite("HudBox.png");
	_menuText = new HudText();
	_menuButton = new MenuButton(_window, _menuButtonBox->sprite);
	_winText = new HudText();

	OrganizePanel();
}

void WinScreen::OrganizePanel() {
	_menuText->_text.setString("Menu");
	_menuButton->SetPosition(300,0);
	_menuButtonBox->sprite.setPosition(300, 0);
	_menuText->_text.setPosition(300, 0);

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
	_window->draw(_menuButtonBox->sprite);
	_window->draw(_menuText->_text);

	_window->draw(_winText->_text);

	_window->popGLStates();
}

