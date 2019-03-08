#ifndef BUTTON_H
#define BUTTON_H

#include "SFML\Graphics.hpp"

class Button
{
public:
	Button(sf::RenderWindow *aWindow,sf::Sprite _buttonSprite);

	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f _pos);
	virtual void Update();

	bool scaled = false;

private:
	int _width;
	int _heigth;
	bool _clicked = true;

	sf::Vector2f _position;
	sf::Vector2u _size;
	sf::Sprite _sprite;
	sf::RenderWindow *_window;

	virtual void OnClick();

};

#endif // !Button_H