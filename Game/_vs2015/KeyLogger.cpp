#include "KeyLogger.h"
#include "SFML/Window.hpp"
#include <sstream>
#include <string>

KeyLogger::KeyLogger()
{
	for (int i = 0; i < 25; i++)
	{
		_keyStates[i] = false;
	}
}

KeyLogger::~KeyLogger()
{

}

sf::Keyboard::Key KeyLogger::GetKeyDown()
{

	sf::Keyboard::Key pressedKey = sf::Keyboard::Unknown;
	for (int i = 0; i < 25; i++)
	{
		bool keyPressed = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
		if (keyPressed && !_keyStates[i])
		{
			_keyStates[i] = true;
			pressedKey = (sf::Keyboard::Key)i;
		}
		else if(!keyPressed && _keyStates[i])
		{
			_keyStates[i] = false;
		}
	}
	return pressedKey;
}

bool KeyLogger::SFKey2Char(char * outputChar)
{
	bool upperCase = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

	sf::Keyboard::Key key = GetKeyDown();
	if (key == sf::Keyboard::Key::Unknown)
	{
		*outputChar = ' ';
		return false;
	}
	int ret = upperCase ? 65 : 97;
	*outputChar = ret + key;
	return true;

}
bool KeyLogger::SFKey2String(std::string* outputString)
{
	char key;
	bool ret = SFKey2Char(&key);
	*outputString = Char2String(key);
	return ret;
}

std::string KeyLogger::Char2String(char character)
{
	std::stringstream ss;
	std::string s;

	ss << character;
	ss >> s;
	return s;
}