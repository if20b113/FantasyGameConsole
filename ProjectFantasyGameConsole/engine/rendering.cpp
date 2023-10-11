#include <vector>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer.h"

#include "lua.hpp"
#include "sol/sol.hpp"

#include "_FantasyGameEngine.hpp"

namespace FantasyGameEngine
{
    void render_rect(const FGE_Renderer* renderer, 
        const glm::vec2& pos, 
        const glm::vec2& size, 
        float r, float g, float b)
    {
        SDL_Rect rect = { 
            pos.x,
            pos.y,
            size.x,
            size.y 
        };
        SDL_SetRenderDrawColor(renderer->sdl_renderer, r * 255, g * 255, b * 255, 255);
        SDL_RenderFillRect(renderer->sdl_renderer, &rect);
    }

    FGE_ImageHandle load_image(const FGE_Renderer* renderer, const char* path)
    {
        FGE_ImageHandle this_image_handle = fge_state.next_image_handle++;
        FGE_Image img;
        img.sdl_texture = IMG_LoadTexture(renderer->sdl_renderer, path);
        SDL_QueryTexture(img.sdl_texture, NULL, NULL, &img.w, &img.h);
        fge_state.images.insert({ this_image_handle, img });
        return this_image_handle;
    }

    void render_image(const FGE_Renderer* renderer, const glm::vec2& pos, const FGE_ImageHandle& image)
    {
        auto img = fge_state.images.at(image);

        SDL_Rect rect; 
        rect.x = pos.x; 
        rect.y = pos.y; 
        rect.w = img.w; 
        rect.h = img.h;

        SDL_RenderCopy(renderer->sdl_renderer, img.sdl_texture, NULL, &rect);
    }

    void render_image(const FGE_Renderer* renderer, 
        const glm::vec2& pos, 
        const glm::vec2& size, 
        const FGE_ImageHandle& image)
    {
        auto img = fge_state.images.at(image);

        SDL_Rect rect;
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = size.x;
        rect.h = size.y;

        SDL_RenderCopy(renderer->sdl_renderer, img.sdl_texture, NULL, &rect);
    }

    void render_text(const FGE_Renderer* renderer, const glm::vec2& pos, const char* text)
    {
        SDL_Surface* text_surface = TTF_RenderUTF8_Blended(fge_state.font, text, { 0xFF, 0xFF, 0xFF, 0 });
        print_sdl_error("after TTF_RenderUTF8_Blended");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer->sdl_renderer, text_surface);
        print_sdl_error("after SDL_CreateTextureFromSurface");
        SDL_Rect text_rect = { pos.x, pos.y, text_surface->w, text_surface->h };
        SDL_RenderCopy(renderer->sdl_renderer, texture, 0, &text_rect);
        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(texture);
    }
}