#include "Tetromino.h"

#include "Grid.h"

std::array<Block, 4>& Tetromino::GetBlocks()
{
    return blocks_;
}

const std::array<Block, 4>& Tetromino::GetBlocks() const
{
    return blocks_;
}

bool Tetromino::CanMove(const Grid& grid, const lm2_v2_i8& input) const
{
    for (const Block& block : blocks_)
    {
        if (grid.IsOccupied(block.x + input.x, block.y - input.y))
        {
            return false;
        }
    }
    
    return true;
}

void Tetromino::Move(const lm2_v2_i8& input)
{
    for (Block& block : blocks_)
    {
        block.x += input.x;
        block.y -= input.y;
    }
}
