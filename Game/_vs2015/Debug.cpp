#include "Debug.h"
#include <iostream>
#include <string>
#include "mge/config.hpp"

Debug::Debug()
{

}

void Debug::Log(std::string message, DebugLevel DebugLevel)
{
	if (config::DEBUG_LEVEL >= DebugLevel)
		std::cout << message << std::endl;
}

void Debug::LogError(std::string errorMessage)
{
	if (config::DEBUG_LEVEL == DebugLevel::NONE)return;
	std::cerr << errorMessage << std::endl;
}