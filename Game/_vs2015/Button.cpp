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

void Button::SetPosition(sf::Vector2f pos) {
	_position.x = pos.x;
	_position.y = pos.y;
}

void Button::OnClick() 
{

}

void Button::Update() 
{
	sf::Vector2i position = sf::Mouse::getPosition(*_window);
	if (position.x > _position.x - _size.x/2 && position.x < _position.x + _size.x / 2
		&& position.y > _position.y - _size.y/2 && position.y < _position.y + _size.y / 2)
	{
		scaled = true;
		if (_clicked && sf::Mouse::isButtonPressed(sf::Mouse::Button(0)))
		{
			OnClick();
			_clicked = false;
		}
	}
	else if(_clicked == false)
	{
		_clicked = true;
	}
	else scaled = false;
}