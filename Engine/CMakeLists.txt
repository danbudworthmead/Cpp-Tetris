cmake_minimum_required(VERSION 3.20)

add_library(Engine STATIC
        include/Grid.h
        src/Grid.cpp
        include/Block.h
        include/Tetromino.h
        src/Tetromino.cpp
        include/TetrominoFactory.h
        src/TetrominoFactory.cpp
)

target_include_directories(Engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)