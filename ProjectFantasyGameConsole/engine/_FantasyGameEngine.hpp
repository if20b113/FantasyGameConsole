#ifndef _FANTASYGAMEENGINE_HPP
#define _FANTASYGAMEENGINE_HPP
    
#include "FantasyGameEngine.hpp"

namespace FantasyGameEngine {

struct FGE_Renderer
{
    SDL_Renderer* sdl_renderer;
};

struct FGE_Image
{
    SDL_Texture* sdl_texture;
    int w, h;
};

struct EngineState
{
    FGE_ImageHandle next_image_handle = 1;
    std::unordered_map<FGE_ImageHandle, FGE_Image> images;
    TTF_Font* font;
};

extern EngineState fge_state;

void print_sdl_error(const char* note);

}

#endif