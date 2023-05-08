#include <stdio.h>

#include "SDL.h"
#include "SDL_ttf.h"

#include "lua.hpp"
#include "sol/sol.hpp"

#include "FantasyGameEngine.hpp"

namespace FGE {

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

    int native_func(int param1)
    {
        printf("called native func with param %d!\n", param1);
        return param1 * 2;
    }

    void print_lua_entities(const sol::table &entities)
    {
        for (const auto& key_value_pair : entities) 
        {
            auto entity_id = key_value_pair.first.as<std::string>();
            auto entity = key_value_pair.second.as<sol::table>();

            printf("entity %s position: %f\n", entity_id.c_str(), (float)entity["pos"]);
        }
    }

    void test_lua()
    {
        sol::state lua {};
        lua.open_libraries(sol::lib::base);

        lua.script("print('Hello World from compiled lua string!')");
    
        lua.set_function("native_func", &native_func);
        
        lua.script_file("assets/scripts/test.lua");

        const std::function<void(float)>& lua_func = lua["scripting_example_update"];
        
        printf("calling scripting_example_update from c++ ...\n");
        lua_func(2);
        print_lua_entities(lua["entities"]);


        printf("calling scripting_example_update from c++ again...\n");
        lua_func(3);
        print_lua_entities(lua["entities"]);

        auto error_result = lua.script_file("assets/scripts/test_error.lua", &sol::script_pass_on_error);
        if (!error_result.valid())
        {
            sol::error error = error_result;
            std::cout << error.what() << std::endl;
        }
    }

    int add(int a, int b)
    {
        return a + b;
    }

}
