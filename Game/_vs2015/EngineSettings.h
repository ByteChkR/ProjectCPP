#ifndef ENGINESETTINGS_HPP
#define ENGINESETTINGS_HPP
#include <string>
#include "lua.hpp"
struct EngineSettings
{
public:
	EngineSettings(std::string file);
	int GetWidth();
	int GetHeight();
	std::string GetWindowName();
	int GetFPSTarget();

	static EngineSettings* settings;

private:
	int _width, _height, _fpsTarget;
	std::string _windowName;
};

#endif // !ENGINESETTINGS_HPP
