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
	int GetMSAASampleCount();
	bool GetWindowMode();
	bool GetVSyncEnabled();

	void SetWidth(int newWidth);
	void SetHeight(int newWidth);
	void SetFPSTarget(int newWidth);
	void SetMSAASamples(int samples);
	void SetVSync(bool enable);
	void SetWindowMode(bool windowed);
	void SetWindowName(std::string name);

	static EngineSettings* settings;

private:
	int _width, _height, _fpsTarget, _msaaSamples, _vSync, _windowMode;
	std::string _windowName;
};

#endif // !ENGINESETTINGS_HPP
