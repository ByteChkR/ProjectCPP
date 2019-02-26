#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h"
#include "LoadingScreen.h"
#include "MenuButton.h"
#include "Credits.h"
#include "GL/glew.h"

Credits::Credits(sf::RenderWindow *aWindow) {

	_window = aWindow;
	_background = new HudSprite("credits.png");

	_menuButtonBox = new HudSprite("cancel_button.png",1.05f);
	_menuButton = new MenuButton(_window, _menuButtonBox->sprite);

	OrganizeScreen();
}

void Credits::OrganizeScreen() {
	_background->sprite.setPosition(_background->sprite.getTexture()->getSize().x / 2, _background->sprite.getTexture()->getSize().y / 2);

	_menuButtonBox->sprite.setPosition(_background->sprite.getPosition().x + 255, _background->sprite.getPosition().y - 375);
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

	if (_menuButton->scaled) _window->draw(_menuButtonBox->scaledSprite);
	else _window->draw(_menuButtonBox->sprite);

	_window->popGLStates();
}