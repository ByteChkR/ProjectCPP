#ifndef KEYLOGGER_HPP

#define KEYLOGGER_HPP
#include "SFML/Window.hpp"
#include <sstream>
#include <string>
class KeyLogger
{
public:
	KeyLogger();
	~KeyLogger();
	sf::Keyboard::Key GetKeyDown();
	bool SFKey2Char(char * outputChar);
	bool SFKey2String(std::string* outputString);
	std::string Char2String(char character);

private:
	bool _keyStates[26];
};

#endif // 
