#define SDL_MAIN_HANDLED
#include "SDL.h"
#include<cstdlib>


#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer.h"

#include "lua.hpp"
#include "sol/sol.hpp"

#include "FantasyGameEngine.hpp"
#include "CollisionDetection.hpp"
#include "TetrisRenderer.h"
#include "UIRenderer.h"

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
            {1    },
            {1,1,1},
        },
        {
            {1,1  },
            {1    },
            {1    }
        },
        {
            {1,1,1},
            {0,0,1}
        },
        {
            {0,0,1},
            {0,0,1},
            {0,1,1}
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
    },
    {
        {
            {1,1},
            {1,1}
        }
    },
    {
        {
            {0,1    },
            {0,1    },
            {0,1    },
            {0,1    }
        },
        {
            {       },
            {1,1,1,1}
        }
    },
    {
        {
            {1,1  },
            {0,1,1},
        },
        {
            {0,0,1},
            {0,1,1},
            {0,1  }
        },
        {
            {     },
            {1,1  },
            {0,1,1}
        },
        {
            {0,1  },
            {1,1  },
            {1    }
        }
    },
    {
        {
            {0,1,1},
            {1,1  },
        },
        {
            {0,1  },
            {0,1,1},
            {0,0,1}
        },
        {
            {     },
            {0,1,1},
            {1,1  }
        },
        {
            {1    },
            {1,1  },
            {0,1  }
        }
    },
    };
       

    constexpr int grid_size_x = 15;
    constexpr int grid_size_y = 25;
    constexpr int cell_size_x = 25;
    constexpr int cell_size_y = 25;
    ;

    struct GameState {
        bool started = false;

        int tick_timer = 0;

        int score = 0;

        FGE_ImageHandle img;
        FGE_ImageHandle blocks;
        TetrisRenderer FieldRenderer;
        UIRenderer uirenderer;

        glm::ivec2 active_piece_pos = { 5, 0 };
        const glm::ivec2 pos_null = { -1, -1 };
        int active_piece = 0; // -1 means no piece active
        int next_piece = -1; // -1 means no piece
        int hold_slot = -1; // -1 means no piece
        int orientation = 0;
        int nextpiececolor = 0;
        int holdpiececolor = 0;
        int currentpiececoloroffset = 0;
        std::array<std::array<int, grid_size_y>, grid_size_x> grid;

        // powerup ids:
        //  0 = none
        //  1 = bullet
        //  2 = delete top row
        int powerup_pickup_type = 0;
        glm::ivec2 powerup_pickup_pos = pos_null;
        int active_powerup = 0;

        int powerup_bullet_count = 0;
        glm::ivec2 powerup_bullet_pos = pos_null;

        void clear_grid()
        {
            for (auto& col : grid)
                for (auto& cell : col)
                    cell = 0;
        }

        void reset_state()
        {
            tick_timer = 0;
            score = 0;
            nextpiececolor = 0;
            holdpiececolor = 0;
            currentpiececoloroffset = 1 + rand() % 8;
            active_piece = generate_next_piece();
            active_piece_pos = { 5, 0 };
            next_piece = generate_next_piece();
            hold_slot = -1;
            orientation = 0;
            clear_grid();

            active_powerup = 0;
            spawn_powerup();

            powerup_bullet_count = 0;
            powerup_bullet_pos = pos_null;
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

                        grid[x][y] = currentpiececoloroffset * columns[col_i][row_i];
                    }
        }

        void rotate_piece(int dir)
        {
            if (active_piece == -1) return;
            int new_orientation = orientation + dir;
            const auto& piece_orientations = pieces[game_state.active_piece];
            const auto& columns = piece_orientations[new_orientation % piece_orientations.size()];
            for (std::size_t col_i = 0; col_i < columns.size(); col_i++)
                for (std::size_t row_i = 0; row_i < columns[col_i].size(); row_i++)
                    if (columns[col_i][row_i] != 0)
                    {
                        int x = row_i + active_piece_pos.x;
                        int y = col_i + active_piece_pos.y;

                        if (x < 0 || x >= grid_size_x || y < 0 || y >= grid_size_y || grid[x][y] != 0)
                        {
                            return;
                        }
                    }

            orientation = new_orientation;
        }

        void init_powerups()
        {
            switch (active_powerup)
            {
            case 1:
                powerup_bullet_count = 3;
                break;
            }
        }

        bool collide()
        {
            if (active_piece == -1) return false;

            bool collided = false;
            bool picked_up_powerup = false;

            const auto& piece_orientations = pieces[game_state.active_piece];
            const auto& columns = piece_orientations[game_state.orientation % piece_orientations.size()];
            for (std::size_t col_i = 0; col_i < columns.size(); col_i++)
                for (std::size_t row_i = 0; row_i < columns[col_i].size(); row_i++)
                    if (columns[col_i][row_i] != 0)
                    {
                        int x = row_i + active_piece_pos.x;
                        int y = col_i + active_piece_pos.y;

                        if (powerup_pickup_pos != pos_null)
                        {
                            if (x == powerup_pickup_pos.x && y == powerup_pickup_pos.y)
                                picked_up_powerup = true;
                        }

                        if (y == grid_size_y - 1 || game_state.grid[x][y + 1] != 0)
                            collided = true;
                    }

            if (collided)
            {
                solidify();
            }

            if (picked_up_powerup)
            {
                active_powerup = powerup_pickup_type;
                printf("got powerup %d\n", active_powerup);
                init_powerups();
                spawn_powerup();
            }

            return collided;
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
            if (!game_state.uirenderer.ispaused) {
                for (std::size_t y = grid_size_y - 1; y > 0; y--)
                {
                    bool row_full = true;
                    for (std::size_t x = 0; x < grid_size_x; x++)
                        if (!grid[x][y])
                        {
                            row_full = false;
                            break;
                        }

                    if (row_full)
                    {
                        for (std::size_t y2 = y; y2 > 0; y2--)
                            for (std::size_t x = 0; x < grid_size_x; x++)
                                grid[x][y2] = grid[x][y2 - 1];
                        for (std::size_t x = 0; x < grid_size_x; x++)
                            grid[x][0] = 0;
                        score += 10;
                    }
                }
            }
        }
        int generate_random_powerup_type()
        {
            return  (tick_timer % 2) + 1;  
        }

        int generate_random_powerup_pos()
        {
            return tick_timer % grid_size_x;
        }

        int generate_next_piece()
        {
            nextpiececolor = 1 + rand() % 8;
            return tick_timer % pieces.size();
        }

        void spawn_powerup()
        {
            std::size_t x = generate_random_powerup_pos();

            for (std::size_t y = 0; y < grid_size_y; y++)
            {
                if (grid[x][y])
                {
                    powerup_pickup_type = generate_random_powerup_type();
                    powerup_pickup_pos = { x, y - 1 };
                    return;
                }
            }

            powerup_pickup_type = generate_random_powerup_type();
            powerup_pickup_pos = { x, grid_size_y - 1 };
        }

        void use_powerup()
        {
            printf("use %d\n", active_powerup);
            printf("check bullet: %d, %d,%d\n", powerup_bullet_count, powerup_bullet_pos.x, powerup_bullet_pos.y);
            switch (active_powerup)
            {
            case 1:
                if (powerup_bullet_count > 0 && powerup_bullet_pos == pos_null)
                {
                    powerup_bullet_count--;
                    powerup_bullet_pos = {
                        active_piece_pos.x + 1,
                        active_piece_pos.y + 1 };
                    puts("created bulled");
                }
                break;
            case 2:
                int delete_y = -1;
                for (std::size_t y = 0; y < grid_size_y; y++)
                {
                    
                    for (std::size_t x = 0; x < grid_size_x; x++)
                    {
                        if (grid[x][y] != 0) 
                        { 
                            delete_y = y;
                            break; 
                        }
                    }
                    if (delete_y != -1) break;
                }
                if (delete_y != -1)
                {
                for (std::size_t delete_x = 0; delete_x < grid_size_x; delete_x++)
                            {
                                grid[delete_x][delete_y] = 0;

                            }
                }
                active_powerup = 0;
                game_state.spawn_powerup();
                break;
            }
        }

        void hold_piece()
        {
            if(hold_slot == -1){
            hold_slot = active_piece;
            holdpiececolor = currentpiececoloroffset;
            active_piece = next_piece;
            currentpiececoloroffset = nextpiececolor;
            next_piece = generate_next_piece();
            active_piece_pos.y = 0;
            }
        }

        void powerup_update_bullet()
        {
            if (powerup_bullet_pos != pos_null)
            {
                powerup_bullet_pos.y++;

                if (powerup_bullet_pos.y == grid_size_y)
                {
                    powerup_bullet_pos = pos_null;
                }
                else if (grid[powerup_bullet_pos.x][powerup_bullet_pos.y])
                {
                    grid[powerup_bullet_pos.x][powerup_bullet_pos.y] = 0;
                    powerup_bullet_pos = pos_null;
                }

                if (powerup_bullet_pos == pos_null && powerup_bullet_count == 0)
                {
                    active_powerup = 0;
                    game_state.spawn_powerup();
                }
            }
        }
        bool checkgameover() 
        {
            for (std::size_t x = 0; x < grid_size_x; x++)
                if(grid[x][1]) return true;

            return false;
        }


    } game_state;

  /* std::vector<std::tuple<std::string, int>> score()
    {


    }*/ 

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

        ImVec4 clear_color = ImVec4(0.85f, 0.55f, 0.60f, 1.00f);

        FGE_Inputs last_inputs = {};
        FGE_Inputs inputs = {};

        FGE_Renderer r;
        r.sdl_renderer = renderer;

        game_state.FieldRenderer.init(&r);
        game_state.uirenderer.init(&r, window_width, window_height);
        game_state.FieldRenderer.calculategridoffset(grid_size_x, grid_size_y, cell_size_x, cell_size_y, window_width, window_height);

        Uint64 timestamp_now = SDL_GetPerformanceCounter();
        Uint64 timestamp_last = 0;

        double tick_timer = 0;

        init_func(&r);

        bool running = true;
        while (game_state.uirenderer.running)
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
                    case SDLK_e: inputs.down |= FGEKC_e; break;
                    case SDLK_h: inputs.down |= FGEKC_h; break;
                    case SDLK_RETURN: inputs.down |= FGEKC_enter; break;
                    case SDLK_ESCAPE: inputs.down |= FGEKC_esc; break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_w: inputs.down &= ~FGEKC_w; break;
                    case SDLK_a: inputs.down &= ~FGEKC_a; break;
                    case SDLK_s: inputs.down &= ~FGEKC_s; break;
                    case SDLK_d: inputs.down &= ~FGEKC_d; break;
                    case SDLK_e: inputs.down &= ~FGEKC_e; break;
                    case SDLK_h: inputs.down &= ~FGEKC_h; break;
                    case SDLK_RETURN: inputs.down &= ~FGEKC_enter; break;
                    case SDLK_ESCAPE: inputs.down &= ~FGEKC_esc; break;
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

          /* ImGui_ImplSDLRenderer_NewFrame();
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
            ImGui::Render();*/ 

            SDL_SetRenderDrawColor(renderer,
                (Uint8)(clear_color.x * 255),
                (Uint8)(clear_color.y * 255),
                (Uint8)(clear_color.z * 255),
                (Uint8)(clear_color.w * 255));

            SDL_RenderClear(renderer);

            render_func(&r, delta);

           // ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

            SDL_RenderPresent(renderer);
        }

        //ImGui_ImplSDLRenderer_Shutdown();
       // ImGui_ImplSDL2_Shutdown();
       // ImGui::DestroyContext();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return;
    }

    void init(const FGE_Renderer* renderer)
    {
        game_state.img = load_image(renderer, "assets/button.png");
        game_state.blocks = load_image(renderer, "assets/blocks.png");
        game_state.reset_state();
        srand((unsigned)time(NULL));
        game_state.currentpiececoloroffset = 1+rand() % 8; 
        game_state.nextpiececolor = 1 + rand() % 8;
       
    }

    void update(const FGE_Inputs& inputs)
    {
        if (game_state.uirenderer.isinGame) {
           if(!game_state.checkgameover()) {
            game_state.tick_timer++;
            if (!game_state.uirenderer.ispaused) {
                if (inputs.down & FGEKC_a) game_state.shift(-1);
                if (inputs.down & FGEKC_d) game_state.shift(+1);
                if (inputs.pressed & FGEKC_w) game_state.rotate_piece(+1);
                if (inputs.pressed & FGEKC_s) game_state.rotate_piece(-1);
                if (inputs.pressed & FGEKC_h) game_state.hold_piece();
                if (inputs.pressed & FGEKC_e) game_state.use_powerup();

                if (game_state.tick_timer % 3 == 0)
                {
                    game_state.shift_rows();

                    if (game_state.collide())
                    {
                        game_state.active_piece_pos = { 5, 0 };
                        game_state.currentpiececoloroffset = 1 + rand() % 8;

                        game_state.active_piece_pos = { 5, 0 };

                        if (game_state.hold_slot != -1)
                        {
                            game_state.active_piece = game_state.hold_slot;
                            game_state.currentpiececoloroffset = game_state.holdpiececolor;
                            game_state.hold_slot = -1;
                        }
                        else
                        {
                            game_state.active_piece = game_state.next_piece;
                            game_state.currentpiececoloroffset = game_state.nextpiececolor;
                            game_state.next_piece = game_state.generate_next_piece();
                        }
                    }
                    else
                        game_state.active_piece_pos.y += 1;
                }
                game_state.powerup_update_bullet();
            }
            if (inputs.pressed & FGEKC_esc) game_state.uirenderer.ispaused = !game_state.uirenderer.ispaused;
            if (game_state.uirenderer.ispaused) 
            {
                if (inputs.pressed & FGEKC_w) game_state.uirenderer.pausebutton -= 1;
                if (inputs.pressed & FGEKC_s) game_state.uirenderer.pausebutton += 1;
                game_state.uirenderer.checkbuttonint();
                if (inputs.pressed & FGEKC_enter) game_state.uirenderer.HandleInput();
            }
           }
           else {
               //game_state.uirenderer.running = false;
               game_state.uirenderer.isenteringName = true;
               game_state.uirenderer.isinGame = false;
               game_state.uirenderer.Gamestarted = false;
               
           }
        }
        else{
            if (game_state.uirenderer.isinMainMenu) 
            {
                if (inputs.pressed & FGEKC_w) game_state.uirenderer.menubutton -= 1;
                if (inputs.pressed & FGEKC_s) game_state.uirenderer.menubutton += 1;
                game_state.uirenderer.checkbuttonint();
            }
            if(game_state.uirenderer.selectGameMode)
            {
                if (inputs.pressed & FGEKC_w) game_state.uirenderer.gamemodebutton -= 1;
                if (inputs.pressed & FGEKC_s) game_state.uirenderer.gamemodebutton += 1;
            }
            if (inputs.pressed & FGEKC_enter) game_state.uirenderer.HandleInput();
        }
        if (game_state.uirenderer.isenteringName)
        {
            if (inputs.pressed & FGEKC_w) game_state.uirenderer.abccounter += 1;
            if (inputs.pressed & FGEKC_s) game_state.uirenderer.abccounter -= 1;
            if (inputs.down & FGEKC_a) game_state.uirenderer.index -= 1;
            if (inputs.down & FGEKC_d) game_state.uirenderer.index += 1;

            game_state.uirenderer.checkbuttonint();
            if (inputs.pressed & FGEKC_enter) game_state.uirenderer.HandleInput();
        }
        if (game_state.uirenderer.nameconfirmed) game_state.uirenderer.addscore(game_state.score);
        if (game_state.uirenderer.startnewgame) 
        {
            if (game_state.uirenderer.Gamestarted) 
            {
                game_state.uirenderer.isinGame = true;
                game_state.reset_state();
                game_state.clear_grid();
                game_state.uirenderer.startnewgame = false;
                
            }
            else 
            {
                game_state.uirenderer.isinGame = true;
                game_state.uirenderer.startnewgame = false;
                game_state.uirenderer.Gamestarted = true;
            }
           
        }

    }

    void render(const FGE_Renderer* renderer, double delta)
    {
        //auto text = std::to_string(delta);
     
        //render_text(renderer, { 5, 5 }, text.c_str());

        auto text = "Score: " + std::to_string(game_state.score);

        game_state.uirenderer.draw_ui();

        if(game_state.uirenderer.isinGame){
        render_text(renderer, { 5, 5 }, text.c_str());
        // render grid
        for (std::size_t x = 0; x < grid_size_x; x++)
            for (std::size_t y = 0; y < grid_size_y; y++)
                game_state.FieldRenderer.RenderBlock(game_state.grid[x][y], x * cell_size_x + game_state.FieldRenderer.gridoffset.x, y * cell_size_y + game_state.FieldRenderer.gridoffset.y, cell_size_x, cell_size_y);
              
        // render active piece
        const auto& piece_orientations = pieces[game_state.active_piece];
        const auto& columns = piece_orientations[game_state.orientation % piece_orientations.size()];
        for (std::size_t col_i = 0; col_i < columns.size(); col_i++)
            for (std::size_t row_i = 0; row_i < columns[col_i].size(); row_i++) 
            {
                if(columns[col_i][row_i] != 0){
                game_state.FieldRenderer.RenderBlock(game_state.currentpiececoloroffset * columns[col_i][row_i],(row_i + game_state.active_piece_pos.x) * cell_size_x + game_state.FieldRenderer.gridoffset.x, (col_i + game_state.active_piece_pos.y) * cell_size_y + game_state.FieldRenderer.gridoffset.y,cell_size_x,cell_size_y);
                }
            }
        { //render next piece
        render_text(renderer, { game_state.FieldRenderer.gridoffset.x + 565, game_state.FieldRenderer.gridoffset.y }, "Next Piece");
        render_rect(renderer, { game_state.FieldRenderer.gridoffset.x + 565,game_state.FieldRenderer.gridoffset.y}, { 150,150 }, 0, 0, 0, 0.5);
        const auto& piece_orientations = pieces[game_state.next_piece];
        const auto& columns = piece_orientations[0];
        for (std::size_t col_i = 0; col_i < columns.size(); col_i++)
            for (std::size_t row_i = 0; row_i < columns[col_i].size(); row_i++)
            {
                if (columns[col_i][row_i] != 0) {
                    game_state.FieldRenderer.RenderBlock(game_state.nextpiececolor * columns[col_i][row_i], game_state.FieldRenderer.gridoffset.x + 600 + 25 * col_i, 100 + 25 * row_i, cell_size_x, cell_size_y);
                }
         }
        }
        render_text(renderer, { game_state.FieldRenderer.gridoffset.x + 565, game_state.FieldRenderer.gridoffset.y + 200 }, "Hold Piece");
        render_rect(renderer, { game_state.FieldRenderer.gridoffset.x + 565,game_state.FieldRenderer.gridoffset.y+200 }, { 150,150 }, 0, 0, 0, 0.5);
        if (game_state.hold_slot != -1)  // render hold piece
        {
            const auto& piece_orientations = pieces[game_state.hold_slot];
            const auto& columns = piece_orientations[0];
            for (std::size_t col_i = 0; col_i < columns.size(); col_i++)
                for (std::size_t row_i = 0; row_i < columns[col_i].size(); row_i++)
                {
                    if (columns[col_i][row_i] != 0) {
                        game_state.FieldRenderer.RenderBlock(game_state.holdpiececolor * columns[col_i][row_i], game_state.FieldRenderer.gridoffset.x + 600 + 25 * col_i, 300 + 25 * row_i, cell_size_x, cell_size_y);
                    }
                }
        }

       
       
        if (game_state.powerup_bullet_pos != game_state.pos_null)
        {

            FantasyGameEngine::render_rect(renderer,
                {
                    game_state.powerup_bullet_pos.x * cell_size_x + game_state.FieldRenderer.gridoffset.x,
                    game_state.powerup_bullet_pos.y * cell_size_y + game_state.FieldRenderer.gridoffset.y
                },
                { cell_size_x, cell_size_y },
                1, 1, 1);
        }

        if (game_state.powerup_pickup_pos != game_state.pos_null)
        {
            if(game_state.powerup_pickup_type == 1){

            FantasyGameEngine::render_rect(renderer,
                {
                    game_state.powerup_pickup_pos.x * cell_size_x + game_state.FieldRenderer.gridoffset.x,
                    game_state.powerup_pickup_pos.y * cell_size_y + game_state.FieldRenderer.gridoffset.y
                },
                { cell_size_x, cell_size_y },
                1, 0, 1);
            }
            else 
            {
                FantasyGameEngine::render_rect(renderer,
                    {
                        game_state.powerup_pickup_pos.x * cell_size_x + game_state.FieldRenderer.gridoffset.x,
                        game_state.powerup_pickup_pos.y * cell_size_y + game_state.FieldRenderer.gridoffset.y
                    },
                    { cell_size_x, cell_size_y },
                    1, 0.5, 0.5);

            }
        }
        }
        if (game_state.uirenderer.ispaused)
        {
            game_state.uirenderer.draw_pause_menu();
        }

        if (game_state.uirenderer.isenteringName)
        {
            game_state.uirenderer.draw_score_ui();
        }
        //game_state.uirenderer.draw_score_ui();

        

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