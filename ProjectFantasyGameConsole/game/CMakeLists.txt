cmake_minimum_required(VERSION 3.23)
project(FantasyGameConsoleProject)

file(GLOB GAME_SOURCE_FILES *.cpp)

message(STATUS "found GAME_SOURCE_FILES as ${GAME_SOURCE_FILES}")

add_executable(FantasyGame ${GAME_SOURCE_FILES})
target_link_libraries(FantasyGame PRIVATE FantasyGameEngine)
target_include_directories(FantasyGame PRIVATE .)