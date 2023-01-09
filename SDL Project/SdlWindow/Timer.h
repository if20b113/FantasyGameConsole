#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <SDL.h>
#include <iostream>
#include <thread>
#include <Windows.h>
#include <SDL_ttf.h>
#include <string>
#include "globals.h"


class Timer
{
	/*
		Timer has 2 tasks:
		Keep an internal timer (clock) to measure the entire time
		Start a separate timer that is displayed to the user in seconds using the SDL renderer.

		The timer needs to be called in a thread, before the renderer is destroyed.
	*/
private:
	bool bIsStarted;
	clock_t timeClock;
	WindowStorage* storage;
	std::thread* userTimerThread = NULL;

	bool doTimer()
	{
		WindowManager manager;
		std::string timeStr = "";
		int minutes = 0;
		int seconds = 0;
		
		bool run = true;
		while (run)
		{
			seconds++;
			Sleep(1000); // use unistd for usleep if not windows.
			if (seconds == 60)
			{
				minutes++;
				seconds = 0;
			}
			adjustTimer(minutes, seconds, &timeStr);
			// Clear old timer
			manager.displayText(0,0,timeStr,*storage);
			if (minutes >= 2)
			{
				run = false;
			}
		}
		return true;
	}
	
	void adjustTimer(const int& minutes, const int& seconds, std::string* time)
	{
		time->clear(); // trash old
		(*time) = "";
		if (minutes >= 10)
		{
			time->append(std::to_string(minutes)); 
			time->append(":"); // 13: (example with 13 mins)
		}
		else
		{
			time->append("0");
			time->append(std::to_string(minutes));
			time->append(":"); // 03: (example with 3 mins)
		}

		if (seconds >= 10)
		{
			time->append(std::to_string(seconds));
		}
		else
		{
			time->append("0");
			time->append(std::to_string(seconds));
		}
	}
public:
	Timer(WindowStorage* store) 
	{
		storage = store;
		bIsStarted = false;
	};

	void use()
	{
		bIsStarted = true;
		doTimer();
	}
	~Timer()
	{
		std::cout << "Lifespan of Timer in ms: " << endClock() << std::endl;
	}
	
	float endClock()
	{
		// return ellapsed seconds
		return static_cast<float>((timeClock = clock() - timeClock))/CLOCKS_PER_SEC;
	}

	/* Example usage (copy paste in main):
	
		WindowManager manager;
		const char* winName = "MyWindow";
		WindowStorage* store = manager.getWindow(manager.createWindow(winName), PER_PTR);
		manager.RenderWindow(store->winRend);
		Timer time(store);
		time.use();
	*/
	

};

#endif

