#include "Button.h"
#include "SFML\Graphics.hpp"
#include "mge\core\AbstractGame.hpp"


Button::Button(sf::RenderWindow *aWindow, sf::Sprite _buttonSprite): _window(aWindow), _sprite(_buttonSprite)
{
	_position = _sprite.getPosition();
	_size = _sprite.getTexture()->getSize();

}

void Button::SetPosition(float x, float y) 
{
	_position.x = x;
	_position.y = y;
}

void Button::OnClick() 
{

}

void Button::Update() 
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button(0)))
	{
		sf::Vector2i position = sf::Mouse::getPosition(*_window);
		if (_clicked && position.x > _position.x && position.x < _position.x + _size.x
			&& position.y > _position.y && position.y < _position.y + _size.y)
		{
			OnClick();
		}
		_clicked = false;
	}
	else if(_clicked == false)
	{
		_clicked = true;
	}
}