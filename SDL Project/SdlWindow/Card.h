#pragma once
#include <sdl.h>
#include <SDL_image.h>
#include <iostream>
#include "audio.h"


class Card
{
public:
    bool isSelected = false;
    bool isFlipped = false;
    bool isValid = true;
    int CardId = 0;
    int CardPicturex = 0;
    int CardPicturey = 0;
    SDL_Texture* tex;
    SDL_Rect srect;
    SDL_Rect drect;
    Audio soundtrack;
    //Card(SDL_Renderer* ren, int CardId, int x, int y);
    void InitCard(SDL_Renderer* ren, int Id , int x, int y, int CardSize);
    void FlipCard();
    void drawCard(SDL_Renderer* ren);

};