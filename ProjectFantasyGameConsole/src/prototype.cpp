#include <stdio.h>

#include "SDL.h"
#include "SDL_ttf.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer.h"

//#include "RmlUi/Core.h"
//#include "RmlUi_Renderer_SDL.h"
//#include "RmlUi_Platform_SDL.h"

#include "lua.hpp"
#include "sol/sol.hpp"

#include "_FantasyGameEngine.hpp"

namespace FantasyGameEngine 
{
    void render_imgui_windows(ImGuiIO& io, bool& show_demo_window, bool& show_another_window, ImVec4& clear_color)
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");

        ImGui::Text("This is some useful text.");
        ImGui::Checkbox("Demo Window", &show_demo_window);
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        ImGui::ColorEdit3("clear color", (float*)&clear_color);

        if (ImGui::Button("Button")) counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    }

    int test_sdl()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) 
        {
            fprintf(stderr, "failed to initialize sdl2: %s\n", SDL_GetError());
            return -1;
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
            return -1;
        }

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

        if (renderer == NULL)
        {
            fprintf(stderr, "failed to create renderer: %s\n", SDL_GetError());
            return -1;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.Fonts->AddFontFromFileTTF("assets/PublicPixel.ttf", 18.0f, NULL, NULL);

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer_Init(renderer);

        /*
        RenderInterface_SDL sdl_render_interface(renderer);
        SystemInterface_SDL sdl_sys_interface;

        Rml::SetRenderInterface(&sdl_render_interface);
        Rml::SetSystemInterface(&sdl_sys_interface);
        Rml::Initialise();

        Rml::Context* rml_ctx = Rml::CreateContext("rml_ctx", Rml::Vector2i(window_width, window_height));
        if (!rml_ctx)
        {
            fprintf(stderr, "failed to create rmlui context\n");
            return -1;
        }

        Rml::LoadFontFace("assets/PublicPixel.ttf");
        Rml::ElementDocument* doc = rml_ctx->LoadDocument("assets/test_doc.rml");
        if (!doc)
        {
            fprintf(stderr, "failed to load rml document\n");
            return -1;
        }

        doc->Show();
        */

        TTF_Init();
        const char* fontFile = "assets/PublicPixel.ttf";
        TTF_Font* font = TTF_OpenFont(fontFile, 32);
        SDL_Surface* text_surface = TTF_RenderUTF8_Blended(font, "Hello TTF!", { 0xFF, 0xFF, 0xFF, 0 });
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_Rect text_rect = { 10, 10, text_surface->w, text_surface->h };

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        bool running = false;
        while (!running)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                //RmlSDL::InputEventHandler(rml_ctx, event);
                if (event.type == SDL_QUIT)
                    running = true;
                if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                    running = true;
            }

            //rml_ctx->Update();

            ImGui_ImplSDLRenderer_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            render_imgui_windows(io, show_demo_window, show_another_window, clear_color);

            ImGui::Render();
            SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
            SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
            
            SDL_RenderClear(renderer);
            
            SDL_RenderCopy(renderer, texture, 0, &text_rect);
            
            //rml_ctx->Render();

            ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
            
            SDL_RenderPresent(renderer);
        }

        ImGui_ImplSDLRenderer_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
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

    void test_imgui()
    {

    }

    int add(int a, int b)
    {
        return a + b;
    }

}
