#ifndef Button_H
#define Button_H

#include "SFML\Graphics.hpp"

class Button
{
public:
	Button(sf::RenderWindow *aWindow,sf::Sprite _buttonSprite);

	void Update();

private:
	int _width;
	int _heigth;

	sf::Vector2f _position;
	sf::Vector2u _size;
	sf::Sprite _sprite;
	sf::RenderWindow *_window;

	virtual void OnClick();

};

#endif // !Button_H