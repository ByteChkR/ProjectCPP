#include "../_vs2015/RetryButton.h"
#include "../_vs2015/HudSprite.h"
#include "../_vs2015/HudText.h""
#include "LoadingScreen.h"
#include "RetryButton.h"
#include "MenuButton.h"
#include "GL/glew.h"

LoadingScreen::LoadingScreen(sf::RenderWindow *aWindow) {

	_window = aWindow;
	_background = new HudSprite("tmpLoading.png");

	OrganizeScreen();
}

void LoadingScreen::OrganizeScreen() {

}

void LoadingScreen::Update() {
	draw();
}

void LoadingScreen::draw() {
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();

	_window->draw(_background->sprite);

	_window->popGLStates();
}