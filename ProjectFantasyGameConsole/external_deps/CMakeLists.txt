cmake_minimum_required(VERSION 3.23)
project(FantasyGameConsoleProject)

find_library(SDL2_LIB_PATH
    NAMES SDL2
    PATHS "${CMAKE_SOURCE_DIR}/external_deps/sdl2/")

find_library(SDL2_TTF_LIB_PATH
    NAMES SDL2_ttf
    PATHS "${CMAKE_SOURCE_DIR}/external_deps/sdl2_ttf/")   

find_library(SDL2_IMAGE_LIB_PATH
    NAMES SDL2_image
    PATHS "${CMAKE_SOURCE_DIR}/external_deps/sdl2_image/lib/x64/")

message(STATUS "found sdl2 as ${SDL2_LIB_PATH}")
message(STATUS "found sdl2_ttf as ${SDL2_TTF_LIB_PATH}")
message(STATUS "found sdl2_image as ${SDL2_IMAGE_LIB_PATH}")

add_library(sdl2 STATIC IMPORTED)
set_target_properties(sdl2 PROPERTIES
    IMPORTED_LOCATION "${SDL2_LIB_PATH}"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external_deps/sdl2/include")

add_library(sdl2_ttf STATIC IMPORTED)
set_target_properties(sdl2_ttf PROPERTIES
    IMPORTED_LOCATION "${SDL2_TTF_LIB_PATH}"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external_deps/sdl2_ttf/include")

add_library(sdl2_image STATIC IMPORTED)
set_target_properties(sdl2_image PROPERTIES
    IMPORTED_LOCATION "${SDL2_IMAGE_LIB_PATH}"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external_deps/sdl2_image/include")

# RMLUI Wants these libs as packages
    set(FreeType_DIR "${CMAKE_SOURCE_DIR}/external_deps/freetype/")
    set(SDL2_DIR "${CMAKE_SOURCE_DIR}/external_deps/sdl2/")
    set(SDL2_IMAGE_LIBRARY "${CMAKE_SOURCE_DIR}/external_deps/sdl2_image/lib/x64/SDL2_image.lib")
    set(SDL2_IMAGE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external_deps/sdl2_image/include/")

add_subdirectory(googletest-1.13.0)
add_subdirectory(sqlite-amalgamation-3400000)
add_subdirectory(lua)
add_subdirectory(imgui-1.89.5)
add_subdirectory(RmlUi-5.1)

add_library(rmlui_sdl STATIC 
    "${CMAKE_SOURCE_DIR}/external_deps/RmlUi-5.1/Backends/RmlUi_Platform_SDL.cpp"
    "${CMAKE_SOURCE_DIR}/external_deps/RmlUi-5.1/Backends/RmlUi_Renderer_SDL.cpp")
target_include_directories(rmlui_sdl PUBLIC "${CMAKE_SOURCE_DIR}/external_deps/RmlUi-5.1/Backends")
target_link_libraries(rmlui_sdl 
    PRIVATE sdl2 sdl2_image
    PUBLIC RmlCore)

add_library(sol2 INTERFACE)
target_link_libraries(sol2 INTERFACE lua)
target_include_directories(sol2 INTERFACE sol2/include)

add_library(external_deps INTERFACE)
target_link_libraries(external_deps INTERFACE sdl2 sdl2_ttf sdl2_image imgui sqlite3 sol2)