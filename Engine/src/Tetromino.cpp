#include "Tetromino.h"

#include "Grid.h"

bool Tetromino::CanMoveDown(const Grid& grid) const
{
    for (const Block& block : blocks_)
    {
        if (grid.IsOccupied(block.x, block.y + 1))
        {
            return false;
        }
    }
    
    return true;
}

void Tetromino::MoveDown()
{
    for (Block& block : blocks_)
    {
        block.y++;
    }
}

std::array<Block, 4>& Tetromino::GetBlocks()
{
    return blocks_;
}

const std::array<Block, 4>& Tetromino::GetBlocks() const
{
    return blocks_;
}
