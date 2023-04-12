#pragma once
#include <SDL.h>
#include <SDL_log.h>


class KeyboardController {

public:
	KeyboardController(int GridRows, int GridColumns);
	Uint8* keyboard;
	//void Keyboardinput(SDL_Event* event);
	void Testinput(const Uint8* keys);
	int currow = 0;
	int curcolum = 0;
	

private:
	int Gridrows = 0;
	int Gridcolumns = 0;


protected:


};