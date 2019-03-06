#ifndef DEBUG_HPP
#include <string>

enum DebugLevel
{
	NONE, //Nothing, NO errors
	FATAL_ERRORS_ONLY, //Atm not used directly.(when you only want to display errors(set to FATAL_ERRORS_ONLY)
	WARNINGS_ERRORS_ONLY, //Only output warnings and errors
	WARNINGS_ERRORS_LOG1, //Simple Logs that are indicating in not to much detail what the engine is doing
	WARNINGS_ERRORS_LOG2, //More Sophisticated Logs. Including stats of operation
	WARNINGS_ERRORS_LOG3, //Almost every log(except of logs in loops that get called a lot of times
	ALL //Everything
};


class Debug
{
public:
	static void Log(std::string message, DebugLevel DebugLevel);
	static void LogError(std::string message);

private:
	Debug();
};



#endif // 
