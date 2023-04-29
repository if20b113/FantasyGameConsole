#include <stdio.h>
#include "FantasyGameEngine.hpp"
#include "SDL.h"
#include "SDL_ttf.h"

namespace FantasyGameEngine {

    void test_sdl()
    {
        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 720;

        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        
        if (SDL_Init(SDL_INIT_VIDEO) < 0) 
        {
            fprintf(stderr, "failed to initialize sdl2: %s\n", SDL_GetError());
            return;
        }
        
        SDL_CreateWindowAndRenderer(
            SCREEN_WIDTH, SCREEN_HEIGHT, 0,
            &window, &renderer);

        if (window == NULL) 
        {
            fprintf(stderr, "failed to create window: %s\n", SDL_GetError());
            return;
        }

        TTF_Init();
        const char* fontFile = "assets/PublicPixel.ttf";
        TTF_Font* font = TTF_OpenFont(fontFile, 32);

        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, "Hello TTF!", { 0xFF, 0xFF, 0xFF, 0 });
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect = { 10, 10, surface->w, surface->h };

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, 0, &rect);
        SDL_RenderPresent(renderer);

        SDL_Delay(2000);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    int add(int a, int b)
    {
        return a + b;
    }

}
