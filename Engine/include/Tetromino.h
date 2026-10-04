#pragma once

#include <array>
#include "Block.h"

class Grid;

class Tetromino
{
    std::array<Block, 4> blocks_;
    
public:
    /*
     * checks the grid positions below each block
     */
    [[nodiscard]] bool CanMoveDown(const Grid& grid) const;
    void MoveDown();
    std::array<Block, 4>& GetBlocks();
    [[nodiscard]] const std::array<Block, 4>& GetBlocks() const;
};
