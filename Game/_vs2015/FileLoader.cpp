#include "FileLoader.h"
#include <experimental/filesystem>
#include <filesystem>
namespace fs = std::experimental::filesystem::v1;
FileLoader::FileLoader() {}
std::vector<std::string> FileLoader::GetFilesFromFolder(std::string directory)
{
	std::vector<std::string> ret = std::vector<std::string>();

	for (const auto & entry : fs::directory_iterator(directory))
	{
		ret.push_back(entry.path().string());
	}

	return ret;
}

EngineSettings FileLoader::ReadEngineSettings(std::string filepath)
{
	bool a = fs::exists(filepath.c_str());
	return EngineSettings(filepath);
}




