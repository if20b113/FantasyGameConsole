#define SDL_MAIN_HANDLED
#include "SDL.h"


#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer.h"

#include "lua.hpp"
#include "sol/sol.hpp"

#include "FantasyGameEngine.hpp"
#include "CollisionDetection.hpp"

namespace FantasyGameEngine
{
    typedef std::vector<std::vector<std::vector<int>>> Piece;

    const std::vector<Piece> pieces = {
        {
            {
                {1    },
                {1    },
                {1,1  },
            },
            {
                {1,1,1},
                {1    },
            },
            {
                {0,1,1},
                {0,0,1},
                {0,0,1}
            },
            {
                {     },
                {0,0,1},
                {1,1,1}
            }
        },
        {
            {
                {     },
                {1,1,1},
            },
            {
                {0,1  },
                {0,1  },
                {0,1  }
            }
        }
    };

    constexpr int grid_size_x = 25;
    constexpr int grid_size_y = 45;
    constexpr int cell_size_x = 15;
    constexpr int cell_size_y = 15;

    struct GameState {
        bool started = false;
        FGE_ImageHandle img;
        glm::ivec2 active_piece_pos = { 5, 0 };
        int active_piece = 0; // -1 means no piece active
        int orientation = 0;
        std::array<std::array<int, grid_size_y>, grid_size_x> grid;

        void clear_grid()
        {
            for (auto& col : grid)
                for (auto& cell : col)
                    cell = 0;
        }

        void reset_state()
        {
            game_state.orientation = 0;
            game_state.active_piece = 0;
            game_state.active_piece_pos = { 5, 0 };
            clear_grid();
        }

        void solidify()
        {
            if (active_piece == -1) return;
            const auto& piece_orientations = pieces[game_state.active_piece];
            const auto& columns = piece_orientations[game_state.orientation % piece_orientations.size()];
            for (std::size_t col_i = 0; col_i < columns.size(); col_i++)
                for (std::size_t row_i = 0; row_i < columns[col_i].size(); row_i++)
                    if (columns[col_i][row_i] != 0)
                    {
                        int x = row_i + active_piece_pos.x;
                        int y = col_i + active_piece_pos.y;
                        if (x < 0 || x >= grid_size_x ||
                            y < 0 || y >= grid_size_y)
                            continue;

                        grid[x][y] = 1;
                    }
        }

        bool collide()
        {
            if (active_piece == -1) return false;
            const auto& piece_orientations = pieces[game_state.active_piece];
            const auto& columns = piece_orientations[game_state.orientation % piece_orientations.size()];
            for (std::size_t col_i = 0; col_i < columns.size(); col_i++)
                for (std::size_t row_i = 0; row_i < columns[col_i].size(); row_i++)
                    if (columns[col_i][row_i] != 0)
                    {
                        int x = row_i + active_piece_pos.x;
                        int y = col_i + active_piece_pos.y;

                        if (y == grid_size_y - 1 || game_state.grid[x][y + 1] != 0)
                        {
                            return true;
                        }
                    }

            return false;
        }

        void shift(int shift_x)
        {
            if (active_piece == -1) return;
            bool free = true;
            const auto& piece_orientations = pieces[game_state.active_piece];
            const auto& columns = piece_orientations[game_state.orientation % piece_orientations.size()];
            for (std::size_t col_i = 0; col_i < columns.size(); col_i++)
            {
                for (std::size_t row_i = 0; row_i < columns[col_i].size(); row_i++)
                {
                    if (columns[col_i][row_i] == 0) continue;

                    int x = row_i + active_piece_pos.x;
                    int y = col_i + active_piece_pos.y;

                    if (shift_x < 0)
                    {
                        if (x == 0 || grid[x - 1][y] != 0)
                        {
                            free = false;
                            break;
                        }
                    }
                    else
                    {
                        if (x == grid_size_x - 1 || grid[x + 1][y] != 0)
                        {
                            free = false;
                            break;
                        }
                    }
                }

                if (!free) break;
            }

            if (free) active_piece_pos.x += shift_x;
        }

        void shift_rows()
        {
            while (true)
            {
                // stop if last row full
                for (std::size_t x = 0; x < grid_size_x; x++)
                    if (grid[x][grid_size_y - 1] == 0)
                        return;

                // else shift rows
                for (std::size_t x = 0; x < grid_size_x; x++)
                    for (std::size_t y = grid_size_y - 1; y >= 1; y--)
                        grid[x][y] = grid[x][y - 1];
            }
        }
    } game_state;

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

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.Fonts->AddFontFromFileTTF("assets/PublicPixel.ttf", 18.0f, NULL, NULL);

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer_Init(renderer);

        TTF_Init();
        fge_state.font = TTF_OpenFont("assets/tahoma.ttf", 32);
        print_sdl_error("after TTF_OpenFont");

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        FGE_Inputs last_inputs = {};
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
            SDL_Event event;

            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);

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
                    case SDLK_w: inputs.down |= FGEKC_w; break;
                    case SDLK_a: inputs.down |= FGEKC_a; break;
                    case SDLK_s: inputs.down |= FGEKC_s; break;
                    case SDLK_d: inputs.down |= FGEKC_d; break;
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
                inputs.pressed = inputs.down & ~last_inputs.down;
                update_func(inputs);
                tick_timer -= tick_length_ms;
                last_inputs.down = inputs.down;
            }

            ImGui_ImplSDLRenderer_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
            ImGui::Begin("debug controls");

            if (ImGui::Button("reset"))
            {
                game_state.reset_state();
            }

            if (ImGui::Button("solidify"))
            {
                game_state.solidify();
            }

            ImGui::End();
            ImGui::Render();

            SDL_SetRenderDrawColor(renderer,
                (Uint8)(clear_color.x * 255),
                (Uint8)(clear_color.y * 255),
                (Uint8)(clear_color.z * 255),
                (Uint8)(clear_color.w * 255));

            SDL_RenderClear(renderer);

            render_func(&r, delta);

            ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

            SDL_RenderPresent(renderer);
        }

        ImGui_ImplSDLRenderer_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return;
    }

    void init(const FGE_Renderer* renderer)
    {
        game_state.img = load_image(renderer, "assets/button.png");
    }

    void update(const FGE_Inputs& inputs)
    {
        if (inputs.down & FGEKC_a) game_state.shift(-1);
        if (inputs.down & FGEKC_d) game_state.shift(+1);
        if (inputs.pressed & FGEKC_w) game_state.orientation += 1;
        if (inputs.pressed & FGEKC_s) game_state.orientation -= 1;

        if (game_state.collide())
        {
            game_state.solidify();
            game_state.active_piece_pos = { 5, 0 };
            game_state.active_piece = 1; // make random

            game_state.shift_rows();
        }
        else
            game_state.active_piece_pos.y += 1;
    }

    void render(const FGE_Renderer* renderer, double delta)
    {
        auto text = std::to_string(delta);

        render_text(renderer, { 5, 5 }, text.c_str());

        // render grid
        for (std::size_t x = 0; x < grid_size_x; x++)
            for (std::size_t y = 0; y < grid_size_y; y++)
                if (game_state.grid[x][y] != 0)
                    FantasyGameEngine::render_rect(renderer,
                        {
                            x * cell_size_x,
                            y * cell_size_y
                        },
                        { cell_size_x, cell_size_y },
                        0.8, 0, 0);

        // render active piece
        const auto& piece_orientations = pieces[game_state.active_piece];
        const auto& columns = piece_orientations[game_state.orientation % piece_orientations.size()];
        for (std::size_t col_i = 0; col_i < columns.size(); col_i++)
            for (std::size_t row_i = 0; row_i < columns[col_i].size(); row_i++)
                if (columns[col_i][row_i] != 0)
                    FantasyGameEngine::render_rect(renderer,
                        {
                            (row_i + game_state.active_piece_pos.x) * cell_size_x,
                            (col_i + game_state.active_piece_pos.y) * cell_size_y,
                        },
                        { cell_size_x, cell_size_y },
                        1, 0, 0);
    }
}

int main()
{
    FantasyGameEngine::run(
        FantasyGameEngine::init,
        FantasyGameEngine::update,
        FantasyGameEngine::render,
        0.1f * 1000);

    return 0;
}


/*
int async_add(int a, int b)
{
    return a + b;
}
int run_engine_tests()
{
    puts("TESTING BasicThreadPool ...");

    FantasyGameEngine::BasicThreadPool btp(5);

    auto work_result_1 = btp.enqueue(async_add, 4, 7);
    auto work_result_2 = btp.enqueue(async_add, 123, 12);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    printf("work result: %d, %d\n",
        work_result_1.get(),
        work_result_2.get());

    puts("\nTESTING LUA...");
    FantasyGameEngine::test_lua();

    puts("\nTESTING SDL...");
    printf("SDL TESTING RETURNED %d\n",
        FantasyGameEngine::test_sdl());

    puts("\nTESTING FS...");
    puts("reading file ...");
    auto test_file = FantasyGameEngine::read_text_from_file("assets/scripts/test.lua");
    std::cout << test_file << std::endl;

    FantasyGameEngine::score_system_init();

    FantasyGameEngine::update_score("adam", 10);
    FantasyGameEngine::update_score("florian", 15);
    FantasyGameEngine::update_score("faisalhanbali", 20); // Names longer than 8 chars can still be saved, without strict mode. Turning on strict mode is probably not worth it.

    for (const auto& e : FantasyGameEngine::get_scores())
        printf("got row from get_scores: %s, %d, %s\n",
            std::get<0>(e).c_str(),
            std::get<1>(e),
            std::get<2>(e).c_str());

    std::this_thread::sleep_for(std::chrono::seconds(2)); // Sleep to test if different timestamp is generated.

    FantasyGameEngine::update_score("adam", 25);

    puts("after update:");
    for (const auto& e : FantasyGameEngine::get_scores())
        printf("got row from get_scores: %s, %d, %s\n",
            std::get<0>(e).c_str(),
            std::get<1>(e),
            std::get<2>(e).c_str());

    FantasyGameEngine::write_text_to_file("test.txt", test_file);

    return 0;
}
*/