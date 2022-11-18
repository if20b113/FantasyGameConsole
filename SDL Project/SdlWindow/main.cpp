#include <SDL.h>
#include "Audio.h"
#include <iostream>

bool isRunning;
void handleEvents();


int main(int argc, char* argv[])
{

	Audio examplesound;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Hello world!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_SetWindowMinimumSize(window, 100, 100);


	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	isRunning = true;



	while (isRunning) {
		examplesound.load("C:/InnoLab SDL/BasicSDL/BasicSDL/PinkPanther60.wav");
		examplesound.play();
		handleEvents();
		SDL_Surface* image = SDL_LoadBMP("C:/InnoLab SDL/BasicSDL/BasicSDL/x64/Debug/image.bmp");
		if (!image) {
			std::cout << "Fail to load image" << std::endl;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
		SDL_Rect dstrect = { 5, 5, 320, 240 };
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
	}

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