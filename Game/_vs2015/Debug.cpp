#include "Debug.h"
#include <iostream>
#include <string>

Debug::Debug()
{

}

void Debug::Log(std::string message)
{
	std::cout << message << '\n';
}

void Debug::LogError(std::string errorMessage)
{
	std::cerr << errorMessage << '\n';
}