#pragma once
#include <sdl.h>
#include <SDL_image.h>
#include <iostream>
#include "audio.h"
#include "Card.h"



class MemoryGrid
{
public:
    //Button(SDL_Renderer* ren);
    //virtual ~Button();
    Card MemoryGrid[5][5];
    int gridStartx = 50;
    int gridStarty = 50;
    int MemoryTotalwidth;
    int MemoryTotalheight;
    int GridRows;
    int GridColumns;
    int CardSize = 200;
    int CardsLeft = 0;
    void InitGrid(SDL_Renderer* ren, int rows, int columns, int screenwidth, int screenhight);
    void CalculateGridCardsize();
    void CenterGrid();
    void drawCards(SDL_Renderer* ren);

};