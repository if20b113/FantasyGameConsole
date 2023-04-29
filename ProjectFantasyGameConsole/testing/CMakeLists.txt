cmake_minimum_required(VERSION 3.23)
project(FantasyGameConsoleProject)

include(googletest)

add_executable(TestExe test.cpp)
target_link_libraries(TestExe PRIVATE gtest_main FantasyGameEngine)
gtest_discover_tests(TestExe WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/export")