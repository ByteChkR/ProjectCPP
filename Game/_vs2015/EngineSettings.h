#ifndef ENGINESETTINGS_HPP
#define ENGINESETTINGS_HPP
#include <string>
#include "lua.hpp"
struct EngineSettings
{
public:
	EngineSettings(const char* file);
	int GetWidth();
	int GetHeight();
	std::string GetWindowName();

private:
	int _width, _height;
	std::string _windowName;
};

#endif // !ENGINESETTINGS_HPP
