#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

class FontEngine {
public:
    FontEngine();
    ~FontEngine();

    bool loadFont(const std::string& fontPath, const int fontSize);
    void drawText(SDL_Renderer* renderer, const int fontIndex, const std::string text, SDL_Rect destination) const;

private:
    std::vector<TTF_Font*> m_fonts;
    // we store the different fonts we will be using in a vector, so we dont have to load every font repeatedly if used multiple times
};
