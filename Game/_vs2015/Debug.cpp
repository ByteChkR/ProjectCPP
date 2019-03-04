#include "Debug.h"
#include <iostream>
#include <string>

Debug::Debug()
{

}

void Debug::Log(std::string message)
{
	std::cout << message << std::endl;
}

void Debug::LogError(std::string errorMessage)
{
	std::cerr << errorMessage << std::endl;
}