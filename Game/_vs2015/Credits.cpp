#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "LoadingScreen.h"
#include "MenuButton.h"
#include "Credits.h"
#include "GL/glew.h"

Credits::Credits(sf::RenderWindow *aWindow) {

	_window = aWindow;
	_background = new HudSprite("tmpLoading.png");

	_menuText = new HudText();
	_menuButtonBox = new HudSprite("HudBox.png",0.8f);
	_menuButton = new MenuButton(_window, _menuButtonBox->sprite);

	OrganizeScreen();
}

void Credits::OrganizeScreen() {
	_background->sprite.setPosition(_background->sprite.getTexture()->getSize().x / 2, _background->sprite.getTexture()->getSize().y / 2);

	_menuText->_text.setString("Menu");
	_menuButtonBox->sprite.setPosition(500, 500);
	_menuText->_text.setPosition(_menuButtonBox->sprite.getPosition());
	_menuButtonBox->scaledSprite.setPosition(_menuButtonBox->sprite.getPosition());
	_menuButton->SetPosition(_menuButtonBox->sprite.getPosition());
}

void Credits::Update() {
	draw();
	_menuButton->Update();
}

void Credits::draw() {
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_background->sprite);

	_window->draw(_menuText->_text);
	if (_menuButton->scaled) _window->draw(_menuButtonBox->scaledSprite);
	else _window->draw(_menuButtonBox->sprite);

	_window->popGLStates();
}