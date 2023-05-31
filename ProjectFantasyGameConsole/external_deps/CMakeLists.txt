cmake_minimum_required(VERSION 3.23)
project(FantasyGameConsoleProject)

add_subdirectory(googletest-1.13.0)
add_subdirectory(lua)

find_library(SDL2_LIB_PATH
    NAMES SDL2
    PATHS "${CMAKE_SOURCE_DIR}/external_deps/sdl2/")

find_library(SDL2_TTF_LIB_PATH
    NAMES SDL2_ttf
    PATHS "${CMAKE_SOURCE_DIR}/external_deps/sdl2_ttf/")   

find_library(SDL2_IMAGE_LIB_PATH
    NAMES SDL2_image
    PATHS "${CMAKE_SOURCE_DIR}/external_deps/sdl2_image/")

find_library(SDL2_MIXER_LIB_PATH
    NAMES SDL2_mixer
    PATHS "${CMAKE_SOURCE_DIR}/external_deps/SDL2_mixer-2.6.3/")

message(STATUS "found sdl2 as ${SDL2_LIB_PATH}")
message(STATUS "found sdl2_ttf as ${SDL2_TTF_LIB_PATH}")
message(STATUS "found sdl2_image as ${SDL2_IMAGE_LIB_PATH}")
message(STATUS "found sdl2_mixer as ${SDL2_MIXER_LIB_PATH}")

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

add_library(sdl2_mixer STATIC IMPORTED)
set_target_properties(sdl2_mixer PROPERTIES
    IMPORTED_LOCATION "${SDL2_MIXER_LIB_PATH}"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external_deps/SDL2_mixer-2.6.3/include")

add_library(sol2 INTERFACE)
target_link_libraries(sol2 INTERFACE lua)
target_include_directories(sol2 INTERFACE sol2/include)

add_library(external_deps INTERFACE)
target_link_libraries(external_deps INTERFACE sdl2 sdl2_ttf sdl2_image sdl2_mixer sol2)
