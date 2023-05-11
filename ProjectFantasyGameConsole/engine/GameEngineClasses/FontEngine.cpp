#include "FontEngine.h"
#include <iostream>

FontEngine::FontEngine()
{
    if (TTF_Init() == -1)
    {
        std::cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl;
    }
    else
    {
        std::cout << "TTF_Init() succeeded -> SDL2_ttf system ready to go!" << std::endl;
    }
}

FontEngine::~FontEngine()
{
    TTF_Quit();
}

bool FontEngine::loadFont(const std::string& fontPath, const int fontSize)
{
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font)
    {
        std::cout << "TTF_OpenFont() failed: " << TTF_GetError() << std::endl;
        return false;
    }
    std::cout << "TTF_OpenFont() succeeded" << std::endl;
    m_fonts.push_back(font);
    return true;
}

void FontEngine::drawText(SDL_Renderer* renderer, const int fontIndex, const std::string text, SDL_Rect destination) const
{
    TTF_Font* font = m_fonts[fontIndex];
    if (font == nullptr)
    {
        std::cout << "FontEngine::drawText() failed: font is nullptr" << std::endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 255, 255, 255, 255 });
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, nullptr, &destination);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
