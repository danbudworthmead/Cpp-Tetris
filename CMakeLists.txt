cmake_minimum_required(VERSION 3.20)
project(Tetris)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include (FetchContent)

FetchContent_Declare(
        libmath2
        GIT_REPOSITORY https://github.com/luppichristian/libmath2.git
        GIT_TAG main
)

set(LM2_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(libmath2)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.9.1
)

FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(
        lodepng
        GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
        GIT_TAG master
)

FetchContent_GetProperties(lodepng)
if (NOT lodepng_POPULATED)
    FetchContent_Populate(lodepng)
endif ()

add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
target_include_directories(lodepng PUBLIC ${lodepng_SOURCE_DIR})

enable_testing()

add_subdirectory("Engine")
add_subdirectory("Engine.Tests")

add_executable(Tetris src/main.cpp)

target_link_libraries(Tetris PRIVATE Engine)