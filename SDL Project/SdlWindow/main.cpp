#include <SDL.h>
#include "Audio.h"
#include <iostream>

bool isRunning;
void handleEvents();
using namespace std;
void changeColor(SDL_Renderer* renderer);


int main(int argc, char* argv[])
{

	Audio examplesound;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Hello world!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_SetWindowMinimumSize(window, 100, 100);


	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	isRunning = true;

	changeColor(renderer);

	while (isRunning) {
		examplesound.load("C:/Users/dario/source/repos/FantasyGameConsole/SDL Project/SdlWindow/PinkPanther60.wav");
		examplesound.play();
		handleEvents();
		SDL_Surface* image = SDL_LoadBMP("C:/Users/dario/source/repos/FantasyGameConsole/SDL Project/SdlWindow/x64/Debug/rickastley.bmp");
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

void changeColor(SDL_Renderer* renderer) {
	char option = '?';
	int color = 1;
	while (option != 'y' && option != 'n') {
		cout << endl << "Do you want to change the background color? y/n ";
		cin >> option;
		if (option == 'y') {
			while (color != 0) {
				cout << endl << "Choose color: red(1), green(2), blue(3) or stop changing colors(0) ";
				cin >> color;
				switch (color) {
				case 1:
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					SDL_RenderClear(renderer);
					SDL_RenderPresent(renderer);
					break;
				case 2:
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					SDL_RenderClear(renderer);
					SDL_RenderPresent(renderer);
					break;
				case 3:
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					SDL_RenderClear(renderer);
					SDL_RenderPresent(renderer);
					break;
				case 0:
					cout << endl << "You stopped changing colors.";
					break;
				default:
					cout << endl << "Invalid input!";
				}
				cout << endl << "The color is: " << color;
			}
		}
		else if (option != 'y' && option != 'n') {
			cout << endl << "Invalid input!";
		}
		else if (option == 'n') {
			cout << endl << "You chose not to change the color.";
		}
	}

}