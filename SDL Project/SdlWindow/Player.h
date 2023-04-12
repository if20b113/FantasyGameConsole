#pragma once
#include <sdl.h>
#include <SDL_image.h>
#include <iostream>
#include "Card.h"

class Player
{
public:
    int Score = 0;
    Card* ChosenCard1;
    Card* ChosenCard2;
    void GetCard(Card* CardtoGet);
    void CheckCards();
};