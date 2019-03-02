#ifndef DEBUG_HPP
#include <string>

class Debug
{
public:
	static void Log(std::string message);
	static void LogError(std::string message);

private:
	Debug();
};



#endif // 
