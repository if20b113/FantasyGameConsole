cmake_minimum_required(VERSION 3.23)
project(FantasyGameConsoleProject)

enable_testing()
include(CTest)

add_subdirectory(external_deps)
add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(testing)