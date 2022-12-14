#include <SDL.h>
#include "Audio.h"
#include "Timer.h"
#include <iostream>
#include <SDL_ttf.h>
#include <string>
#include <SDL_keyboard.h>

bool isRunning;
void handleEvents();
using namespace std;
void changeColor(SDL_Renderer* renderer);
void arrowSounds();

void use(Timer* time)
{
	time->use();
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Hello world!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_SetWindowMinimumSize(window, 100, 100);


	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderPresent(renderer);
	isRunning = true;

	Audio soundtrack;
	soundtrack.load("Resources/soundtrack.wav");
	soundtrack.play();
	//changeColor(renderer);
	/*while (isRunning) {
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
	}*/

	arrowSounds();
	return 0;
}

void arrowSounds()
{
	Audio up;
	Audio down;
	Audio left;
	Audio right;
	up.load("Resources/Button(Choice).wav");
	down.load("Resources/Button(class).wav");
	left.load("Resources/Button(click).wav");
	right.load("Resources/Button(confirm).wav");
	while (isRunning) // Game loop
	{
		// SDL_scancode.h shows you key keyboard key events
		/*
		    SDL_SCANCODE_RIGHT = 79,
			SDL_SCANCODE_LEFT = 80,
			SDL_SCANCODE_DOWN = 81,
			SDL_SCANCODE_UP = 82,
		*/

		/*
			In SDL events, there is a union which multiple Event types live inside.
			One of these event types is SDL_KeyboardEvent, defined in SDL_Event under "key".
			Viewing the definition of SDL_Event, you will see "keyboard events", which limits to key up, down and a few other
			The information of which key is pressed resides inside those structures. So we need to access KeyBoardEvent through SDL_Event,
			and dive deeper until we see the enums for the so called scancodes.
			The scancode corresponding to the button is inside this key event inside.
			We walk through those structures and do another switch statement, examining which button was pressed and react correspondingly.
		*/
		SDL_Event event;
		while (SDL_PollEvent(&event)) { // https://wiki.libsdl.org/SDL2/SDL_Event
			switch (event.type) {
			case SDL_KEYDOWN: // View definition to see other event types
			{
				switch (event.key.keysym.scancode) // Examine the scancode to see which button was pressed!
				{
				case SDL_SCANCODE_DOWN:
					printf("On DOWN\n");
					down.play();
					break;
				case SDL_SCANCODE_UP:
					printf("On UP\n");
					up.play();
					break;
				case SDL_SCANCODE_RIGHT:
					printf("On RIGHT\n");
					right.play();
					break;

				case SDL_SCANCODE_LEFT:
					printf("On LEFT\n");
					left.play();
					break;
				}
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				printf("On MOUSE UP\n");
				left.play();
				break;
			}
			case SDL_QUIT:
				isRunning = false;
				break;
			default:
				break;
			}
		}
	}
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