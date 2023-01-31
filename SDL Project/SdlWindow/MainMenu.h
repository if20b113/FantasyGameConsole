#pragma once
#pragma once
#include <sdl.h>
#include <SDL_image.h>
#include <iostream>
#include "Button.h"




class MainMenu
{
public:
    bool Start = false;
    bool Quit = false;
    Button startButton;
    Button exitButton;
    MainMenu(SDL_Renderer* ren, int screenwidth, int screenheight);
    void updateButtons();
    void drawButtons(SDL_Renderer* ren);


};