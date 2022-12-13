#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <SDL.h>
#include <iostream>
#include <thread>
#include <Windows.h>
#include <SDL_ttf.h>
#include <string>

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
	SDL_Renderer* renderer;
	std::thread* userTimerThread = NULL;

	SDL_Window* window = NULL;
	SDL_Texture* texture = NULL, *text = NULL;
	TTF_Font* font;
	SDL_Renderer* timerRend = NULL;

	bool doTimer()
	{
		// https://thenumb.at/cpp-course/sdl2/06/06.html
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
			return false;
		}
		// Initialize SDL_ttf
		if (TTF_Init() < 0) 
		{
			std::cout << "Error intializing SDL_ttf: " << TTF_GetError() << std::endl;
			return false;
		}
		SDL_SetRenderDrawColor(timerRend, 255, 255, 255, 255);
		SDL_RenderClear(timerRend);
		window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
		if (!window) {
			std::cout << "Error creating window: " << SDL_GetError() << std::endl;
			return false;
		}

		timerRend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (!timerRend) {
			std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
			return false;
		}

		// Load font
		font = TTF_OpenFont("resources/tahoma.ttf", 20);
		if (!font) {
			std::cout << "Error loading font: " << TTF_GetError() << std::endl;
			return false;
		}
		

		SDL_Rect dest;
		SDL_Color foreground = { 0, 0, 0 };
		std::string timeStr = "00:00";
		SDL_Surface* text_surf = TTF_RenderText_Solid(font, timeStr.c_str(), foreground);
		text = SDL_CreateTextureFromSurface(timerRend, text_surf);

		dest.x = 320 - (text_surf->w / 2.0f);
		dest.y = 240;
		dest.w = text_surf->w;
		dest.h = text_surf->h;
		SDL_RenderCopy(timerRend, text, NULL, &dest);

		SDL_DestroyTexture(text);
		SDL_FreeSurface(text_surf);

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
			text_surf = TTF_RenderText_Solid(font, timeStr.c_str() , foreground);
			text = SDL_CreateTextureFromSurface(timerRend, text_surf);
			SDL_RenderPresent(timerRend);
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
	void initiateUserTimer()
	{
		//bIsStarted = true;
		//std::thread Thread(doTimer);
		//userTimerThread = &Thread;
	}
public:
	Timer(SDL_Renderer* rend) 
	{
		bIsStarted = false;
		if (rend == NULL)
		{
			std::cout << "critical error: passed in renderer for Timer is NULL.\n";
			renderer = NULL;
		}
		else
		{
			timeClock = clock();
			renderer = rend;
			//initiateUserTimer();
		}
	};

	void use()
	{
		bIsStarted = true;
		doTimer();
	}
	~Timer()
	{
		//userTimerThread->join();
		TTF_CloseFont(font);
		SDL_DestroyTexture(texture);
		texture = NULL;

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		window = NULL;
		renderer = NULL;
		std::cout << "Lifespan of Timer in ms: " << endClock() << std::endl;
		TTF_Quit();
		SDL_Quit();
	}
	
	float endClock()
	{
		// return ellapsed seconds
		return static_cast<float>((timeClock = clock() - timeClock))/CLOCKS_PER_SEC;
	}

	

};

#endif

