#pragma once
#include <sdl.h>
#include <SDL_image.h>
#include <iostream>




class Button
{
public:
    SDL_Texture* tex;
    SDL_Rect srect;
    SDL_Rect drect;
    bool isSelected = false;
    //Button(SDL_Renderer* ren);
    //virtual ~Button();
    void InitButton(SDL_Renderer* ren);
    void update();
    void draw(SDL_Renderer* ren);

};


