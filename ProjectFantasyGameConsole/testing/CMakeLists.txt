cmake_minimum_required(VERSION 3.23)
project(FantasyGameConsoleProject)



add_executable(TestExe test.cpp)
target_link_libraries(TestExe PRIVATE gtest_main FantasyGameEngine)
add_test(TestExe TestExe)