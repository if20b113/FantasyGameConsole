#ifndef DEBUGGER_H
#define DEBUGGER_H
// Universal "only include once"

#include <string>
#include <SDL.h>
#include <SDL_log.h>
typedef enum LogType
{
	LOG_NORMAL = 0,
	LOG_DEBUG = 1,
	LOG_ERROR = 2,
	LOG_INFO = 3,
	LOG_VERBOSE = 6,
	LOG_WARN = 7
};

class DEBUGGER // Singleton
{
private:
	// If wanted, a logger worker can be installed here
	// (For instance to save debug logs in the filesystem)
	// Not safe for multithreading by default

	// Usage of the class is very basic at this point in time (sprint 2)
	// Extending the class to its full capabilities will only happen through
	// implementations of classes using SDL functions and variables.
	// For those classes, fitting debug functions will be created that
	// post specific variable contents to get more insight on the matter at hand.

	DEBUGGER() {}
	static DEBUGGER INSTANCE;

public:

	static DEBUGGER& Instance();

	void log(const char* str); // Basic log function parsing into SDL log
	void BreakPoint(void);

	/*
	*
	* Non functioning as in right now.
	* Currently, if an integer is passed in, garbage will be printed.
	template<typename T>
	void logVar(T var, LogType LT)
	{
		std::string str = "Debug Info var: ";
		str += var;
		switch (LT)
		{
		case LOG_NORMAL:
			SDL_Log(str.c_str());
			break;
		case LOG_DEBUG:
			SDL_LogDebug(1, str.c_str());
			break;
		case LOG_ERROR:
			SDL_LogError(2, str.c_str());
			break;
		case LOG_INFO:
			SDL_LogInfo(3, str.c_str());
			break;
		case LOG_VERBOSE:
			SDL_LogVerbose(4, str.c_str());
			break;
		case LOG_WARN:
			SDL_LogWarn(5, str.c_str());
			break;
		}
	}*/

};

#endif

