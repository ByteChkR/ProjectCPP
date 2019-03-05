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
	/*char output;
	if (klogger->SFKey2Char(&output))
	{
		...
	}*/
	bool SFKey2Char(char * outputChar);
	/*std::string output;
	if (klogger->SFKey2String(&output))
	{
		Debug::Log(output);
	}*/
	bool SFKey2String(std::string* outputString);
	std::string Char2String(char character);

private:
	bool _keyStates[26];
};

#endif // 
