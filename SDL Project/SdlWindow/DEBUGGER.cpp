#include "DEBUGGER.h"
#include <SDL.h>
#include <SDL_log.h>

DEBUGGER& DEBUGGER::Instance()
{
	static DEBUGGER INSTANCE;
	return INSTANCE;
}
void DEBUGGER::log(const char* str)
{
	// Function may be expanded to save logs in files
	SDL_Log(str); // Use SDL logger to create the log. Output on console (not on rendered window created)
}

void DEBUGGER::BreakPoint(void) // Change signature if you plan on adding functionality
{
	SDL_TriggerBreakpoint(); // Trigger a breakpoint based on SDL. 
							 // The implementation is questionable since nothing else is done
							 // (you could just use it like that in your functions)
							 // However, one may would like to expand into creating a log and display variables.
}


