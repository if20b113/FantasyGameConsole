#include "SDL.h"
#include "SDL_ttf.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer.h"

#include "lua.hpp"
#include "sol/sol.hpp"

#include "_FantasyGameEngine.hpp"

namespace FantasyGameEngine
{
    EngineState fge_state = {};

    void print_sdl_error(const char* note)
    {
        char err_msg_buf[1024] = {};
        SDL_GetErrorMsg(err_msg_buf, 1024);
        if (err_msg_buf[0] == 0) return;
        printf("sdl error (%s): %s\n", note, err_msg_buf);
    }

    void run(
        FGE_InitFunc init_func,
        FGE_UpdateFunc update_func,
        FGE_RenderFunc render_func,
        double tick_length_ms)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            fprintf(stderr, "failed to initialize sdl2: %s\n", SDL_GetError());
            return;
        }

        const int window_width = 1280;
        const int window_height = 720;

        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

        SDL_Window* window = SDL_CreateWindow(
            "SDL Test",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            window_width,
            window_height,
            window_flags);

        if (window == NULL)
        {
            fprintf(stderr, "failed to create window: %s\n", SDL_GetError());
            return;
        }

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

        if (renderer == NULL)
        {
            fprintf(stderr, "failed to create renderer: %s\n", SDL_GetError());
            return;
        }

        SDL_GL_SetSwapInterval(0);

        TTF_Init();
        fge_state.font = TTF_OpenFont("assets/tahoma.ttf", 32);
        print_sdl_error("after TTF_OpenFont");

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        FGE_Inputs inputs = {};

        FGE_Renderer r;
        r.sdl_renderer = renderer;

        Uint64 timestamp_now = SDL_GetPerformanceCounter();
        Uint64 timestamp_last = 0;

        double tick_timer = 0;

        init_func(&r);

        bool running = true;
        while (running)
        {
            inputs.pressed = 0;

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_WINDOWEVENT &&
                    event.window.event == SDL_WINDOWEVENT_CLOSE &&
                    event.window.windowID == SDL_GetWindowID(window))
                    running = false;

                switch (event.type)
                {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w: inputs.pressed |= FGEKC_w; inputs.down |= FGEKC_w; break;
                    case SDLK_a: inputs.pressed |= FGEKC_a; inputs.down |= FGEKC_a; break;
                    case SDLK_s: inputs.pressed |= FGEKC_s; inputs.down |= FGEKC_s; break;
                    case SDLK_d: inputs.pressed |= FGEKC_d; inputs.down |= FGEKC_d; break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w: inputs.down &= ~FGEKC_w; break;
                    case SDLK_a: inputs.down &= ~FGEKC_a; break;
                    case SDLK_s: inputs.down &= ~FGEKC_s; break;
                    case SDLK_d: inputs.down &= ~FGEKC_d; break;
                    }
                    break;

                default:
                    break;
                }
            }

            SDL_SetRenderDrawColor(renderer, 
                (Uint8)(clear_color.x * 255), 
                (Uint8)(clear_color.y * 255), 
                (Uint8)(clear_color.z * 255), 
                (Uint8)(clear_color.w * 255));

            SDL_RenderClear(renderer);

            timestamp_last = timestamp_now;
            timestamp_now = SDL_GetPerformanceCounter();
            double delta = (double)
            (
                (timestamp_now - timestamp_last)
                * 1000
                / (double)SDL_GetPerformanceFrequency()
            );

            tick_timer += delta;

            while (tick_timer > tick_length_ms)
            {
                update_func(inputs);
                tick_timer -= tick_length_ms;
            }

            render_func(&r, delta);

            SDL_RenderPresent(renderer);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return;
    }
}