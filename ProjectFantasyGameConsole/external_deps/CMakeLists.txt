cmake_minimum_required(VERSION 3.23)
project(FantasyGameConsoleProject)

find_library(SDL2_LIB_PATH
    NAMES SDL2
    PATHS "${CMAKE_SOURCE_DIR}/external_deps/sdl2/")

find_library(SDL2_TTF_LIB_PATH
    NAMES SDL2_ttf
    PATHS "${CMAKE_SOURCE_DIR}/external_deps/sdl2_ttf/")   

message(STATUS "found sdl2 as ${SDL2_LIB_PATH}")
message(STATUS "found sdl2_ttf as ${SDL2_TTF_LIB_PATH}")

add_library(sdl2 STATIC IMPORTED)
set_target_properties(sdl2 PROPERTIES
    IMPORTED_LOCATION "${SDL2_LIB_PATH}"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external_deps/sdl2/include")

add_library(sdl2_ttf STATIC IMPORTED)
set_target_properties(sdl2_ttf PROPERTIES
    IMPORTED_LOCATION "${SDL2_TTF_LIB_PATH}"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external_deps/sdl2_ttf/include")

add_library(external_deps INTERFACE)
target_link_libraries(external_deps INTERFACE sdl2 sdl2_ttf)

include(FetchContent)

#FetchContent_Declare(
#    googletest
#    GIT_REPOSITORY https://github.com/google/googletest.git
#    GIT_TAG release-1.12.1
#)
#FetchContent_MakeAvailable(googletest)

add_subdirectory(googletest-1.13.0)