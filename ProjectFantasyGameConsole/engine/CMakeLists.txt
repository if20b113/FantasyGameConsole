cmake_minimum_required(VERSION 3.23)
project(FantasyGameConsoleProject)

file(GLOB ENGINE_SOURCE_FILES GameEngine/*.cpp GameEngineClasses/*.cpp)

message(STATUS "found ENGINE_SOURCE_FILES as ${ENGINE_SOURCE_FILES}")

add_library(FantasyGameEngine SHARED ${ENGINE_SOURCE_FILES})

target_link_libraries(FantasyGameEngine PRIVATE external_deps)
target_include_directories(FantasyGameEngine 
    PUBLIC include/FGE GameEngine GameEngineClasses
    PUBLIC include)

target_compile_features(FantasyGameEngine PRIVATE cxx_std_17)
set_target_properties(FantasyGameEngine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS 1)