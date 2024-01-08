cmake_minimum_required(VERSION 3.23)
project(FantasyGameConsoleProject)

add_library(imgui STATIC
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_demo.cpp
    backends/imgui_impl_sdl2.cpp
    backends/imgui_impl_sdlrenderer.cpp)
target_include_directories(imgui PUBLIC .)
target_link_libraries(imgui PUBLIC sdl2)