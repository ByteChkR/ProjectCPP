#ifndef FILELOADER_HPP
#define FILELOADER_HPP
#include <filesystem>
#include <vector>
#include "EngineSettings.h"
#include <string>

class FileLoader
{
public:
	static std::vector<std::string> GetFilesFromFolder(std::string directory);
	static EngineSettings ReadEngineSettings(const char* filepath);
private:

	FileLoader();
};

#endif // !FILELOADER_HPP
