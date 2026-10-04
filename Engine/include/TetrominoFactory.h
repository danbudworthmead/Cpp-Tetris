#pragma once
#include <memory>

class Tetromino;

class TetrominoFactory
{
public:
    static std::unique_ptr<Tetromino> Create(int x, int y);
};
