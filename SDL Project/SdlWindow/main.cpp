#include <SDL.h>
#include "DEBUGGER.h"
#include "Audio.h"

bool isRunning;
void handleEvents();


int main(int argc, char* argv[])
{

	Audio examplesound;



	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Hello world!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_SetWindowMinimumSize(window, 100, 100);


	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	isRunning = true;

	while (isRunning) {
		examplesound.load("C:/InnoLab SDL/BasicSDL/BasicSDL/PinkPanther60.wav");
		examplesound.play();
		handleEvents();
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}



	DEBUGGER dbg = DEBUGGER::Instance();
	dbg.log("Example log");
	return 0;
}



void handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);


	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}