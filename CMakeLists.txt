cmake_minimum_required(VERSION 3.20)
project(Tetris)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("Engine")

add_executable(Tetris src/main.cpp)

target_link_libraries(Tetris PRIVATE Engine)