#include <SDL.h>
#include "Audio.h"
#include "Timer.h"
#include <iostream>
#include <SDL_ttf.h>
#include <string>
#include <SDL_keyboard.h>
#include "Scoreboard.h"
#include "MainMenu.h"
#include "KeyboardController.h"
#include "MemoryGrid.h"
#include "Player.h"

bool isRunning;
void handleEvents();
using namespace std;
void changeColor(SDL_Renderer* renderer);
void arrowSounds(Scoreboard highscore, Scoreboard currentScore, Scoreboard highscorePoints, Scoreboard currentPoints, const string path, SDL_Renderer* renderer);

void use(Timer* time)
{
	time->use();
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("SDLMemoryGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);
	SDL_SetWindowMinimumSize(window, 100, 100);


	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	isRunning = true;
	Timer time(renderer);
	MainMenu Menu(renderer, 1600,900);
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	Player Player;

	SDL_RenderSetLogicalSize(renderer, 1600, 900);

	//Audio soundtrack;
	//soundtrack.load("Resources/soundtrack.wav");
	//soundtrack.play();
	//changeColor(renderer);
	/*while (isRunning) {
		examplesound.load("Resources/PinkPanther60.wav");
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

	if (TTF_Init() == -1) {		//initialize SDL_ttf, returns 0 on success, -1 on error.
		std::cout << "\nCould not initialize SDL2_ttf, error: " << TTF_GetError();
	}
	else {
		std::cout << "\nSDL2_ttf system is ready to go!";
	}

	const string path = "resources/PublicPixel.ttf";

	Scoreboard highscore(path, 24, "Highscore: ", { 255, 0, 0, 255 }, renderer);
	Scoreboard currentScore(path, 24, "Current score: ", { 255, 0, 0, 255 }, renderer);

	Scoreboard highscorePoints(0);
	Scoreboard currentPoints(0);

	//highscorePoints.setPoints(0, path, renderer);
	currentPoints.setPoints(0, path, renderer);

	KeyboardController KeyBoardGrid(4, 4);

	KeyboardController KeyBoardMainMenu(1, 2);

	MemoryGrid Grid;

	Card* ChosenCard1 = NULL;
	Card* ChosenCard2 = NULL;

	Grid.InitGrid(renderer, 4, 4, 1600, 900);

	SDL_Event event;
	SDL_PollEvent(&event);

	while (isRunning) // Game loop
	{
		SDL_WaitEvent(&event);

		Menu.updateButtons();

		//highscore.display(20, 20, renderer);
	
		//highscorePoints.display(300, 20, renderer);
		//currentPoints.display(1125, 20, renderer);
		
		//use(&time);


		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYUP:
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				isRunning = false;
			}
			break;

		case SDL_KEYDOWN:
			if (Menu.Start) 
			{
				KeyBoardGrid.Testinput(keys);

			}
			else 
			{
				KeyBoardMainMenu.Testinput(keys);
			}
			if (KeyBoardMainMenu.curcolum == 1 && KeyBoardMainMenu.currow == 0) {

				Menu.exitButton.isSelected = false;
				Menu.startButton.isSelected = true;
				std::cout << "Start button selected\n";
			}
			if (KeyBoardMainMenu.curcolum == 0 && KeyBoardMainMenu.currow == 0) {

				Menu.startButton.isSelected = false;
				Menu.exitButton.isSelected = true;
				std::cout << "Exit button selected\n";
				
			}
			if (keys[SDL_SCANCODE_K]) {
				std::cout << "Enter pressed\n";

				if (Menu.startButton.isSelected) {

					Menu.Start = true;
				}

				if (Menu.exitButton.isSelected) {

					isRunning = false;
				}

				if (Menu.Start)
				{
					Player.GetCard(&Grid.MemoryGrid[KeyBoardGrid.curcolum][KeyBoardGrid.currow]);
				}

				// Grid.MemoryGrid[KeyBoardGrid.curcolum][KeyBoardGrid.currow].FlipCard();
				// std::cout << &Grid.MemoryGrid[KeyBoardGrid.curcolum][KeyBoardGrid.currow];

				/*if (ChosenCard1 != NULL && ChosenCard1 == &Grid.MemoryGrid[KeyBoardGrid.curcolum][KeyBoardGrid.currow]) {

					std::cout << "Card1Unselected\n";
					ChosenCard1->FlipCard();
					ChosenCard1 = NULL;
				}

				else if (ChosenCard2 != NULL && ChosenCard2 == &Grid.MemoryGrid[KeyBoardGrid.curcolum][KeyBoardGrid.currow]) {

					std::cout << "Card2Unselected\n";
					ChosenCard2->FlipCard();
					ChosenCard2 = NULL;
				}

				else if (ChosenCard1 == NULL) {
					ChosenCard1 = &Grid.MemoryGrid[KeyBoardGrid.curcolum][KeyBoardGrid.currow];
					std::cout << "Card1Selected\n";
					ChosenCard1->FlipCard();
					std::cout << ChosenCard2;
				}
				else if (ChosenCard2 == NULL) {
					ChosenCard2 = &Grid.MemoryGrid[KeyBoardGrid.curcolum][KeyBoardGrid.currow];
					std::cout << "Card2Selected\n";
					ChosenCard2->FlipCard();
					std::cout << ChosenCard2;
				}*/
			}
			break;
		}

		

		if (Grid.CardsLeft <= 0) {

			isRunning = false;
		}

		/*
		if (ChosenCard1 != NULL && ChosenCard2 != NULL && ChosenCard1->CardId == ChosenCard2->CardId) {
			ChosenCard1->isValid = false;
			ChosenCard2->isValid = false;
			std::cout << ChosenCard1->CardId;
			std::cout << ChosenCard2->CardId;
			Grid.CardsLeft -= 2;
			
			ChosenCard1 = NULL;
			ChosenCard2 = NULL;
		}*/

		Player.CheckCards();
		currentPoints.setPoints(Player.Score, path, renderer);

		SDL_RenderClear(renderer);
		Menu.drawButtons(renderer);
		if (Menu.Start) {

			Grid.drawCards(renderer);
			currentScore.display(750, 20, renderer);
			currentPoints.display(1125, 20, renderer);
		}
		
		SDL_RenderPresent(renderer);

	}
	//arrowSounds(highscore, currentScore, highscorePoints, currentPoints, path, renderer);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void arrowSounds(Scoreboard highscore, Scoreboard currentScore, Scoreboard highscorePoints, Scoreboard currentPoints, const string path, SDL_Renderer* renderer)
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

		highscore.display(20, 20, renderer);
		currentScore.display(750, 20, renderer);
		highscorePoints.display(300, 20, renderer);
		currentPoints.display(1125, 20, renderer);



		//SDL_RenderPresent(renderer);
		//SDL_RenderClear(renderer);
		//currentPoints.setPoints(10, path, renderer);
		//SDL_RenderPresent(renderer);
		

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
					SDL_RenderClear(renderer);
					currentPoints.setPoints(10, path, renderer);		//example as how to get points
					SDL_RenderPresent(renderer);
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