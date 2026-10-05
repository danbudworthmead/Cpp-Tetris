#pragma once

#include <array>
#include <lm2/vectors/lm2_vector2.h>

#include "Block.h"

class Grid;

class Tetromino
{
    std::array<Block, 4> blocks_;
    
public:
    /*
     * checks the grid positions below each block
     */
    [[nodiscard]] bool CanMove(const Grid& grid, const lm2_v2_i8& input) const;
    void Move(const lm2_v2_i8& input);
    
    std::array<Block, 4>& GetBlocks();
    [[nodiscard]] const std::array<Block, 4>& GetBlocks() const;
};
