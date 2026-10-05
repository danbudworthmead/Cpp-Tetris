#pragma once
#include <memory>
#include <lm2/vectors/lm2_vector2.h>

class Tetromino;

class TetrominoFactory
{
public:
    static std::unique_ptr<Tetromino> Create(const lm2_v2_i8& pos);
};
