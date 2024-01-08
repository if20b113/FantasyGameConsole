cmake_minimum_required(VERSION 3.23)
project(FantasyGameConsoleProject)

add_executable(FantasyGame
    FGEState.cpp
    FileManagement.cpp
    JobManagement.cpp
    main.cpp
    rendering.cpp
    ScoreManagement.cpp
    TetrisGame.cpp
    Tetromino.cpp
    MutEX.cpp
    constants.cpp)

target_link_libraries(FantasyGame PRIVATE external_deps)
target_include_directories(FantasyGame PRIVATE .)
target_compile_features(FantasyGame PRIVATE cxx_std_17)
set_property(TARGET FantasyGame PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/export")


include(googletest)

add_executable(TestExe 
    FGEState.cpp
    FileManagement.cpp
    JobManagement.cpp
    rendering.cpp
    ScoreManagement.cpp
    test.cpp    
    TetrisGame.cpp
    Tetromino.cpp
    MutEX.cpp
    constants.cpp)
target_link_libraries(TestExe PRIVATE gtest_main external_deps)
target_include_directories(TestExe PRIVATE .)
target_compile_features(TestExe PRIVATE cxx_std_17)
gtest_discover_tests(TestExe WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/export")
