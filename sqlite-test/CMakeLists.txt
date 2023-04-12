cmake_minimum_required(VERSION 3.0)

project(SQLite-Test)

add_subdirectory(dep/sqlite-amalgamation-3400000)

add_executable(sqlite-test src/main.cpp)
target_link_libraries(sqlite-test sqlite3)
