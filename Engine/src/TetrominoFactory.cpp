#include "TetrominoFactory.h"

#include "Tetromino.h"

std::unique_ptr<Tetromino> TetrominoFactory::Create(const lm2_v2_i8& pos)
{
    auto ptr = std::make_unique<Tetromino>();
    auto& blocks = ptr->GetBlocks();
    
    blocks[0].pos.x = pos.x + 0;
    blocks[0].pos.y = pos.y + 0;
    
    blocks[1].pos.x = pos.x + 1;
    blocks[1].pos.y = pos.y + 0;
    
    blocks[2].pos.x = pos.x + 0;
    blocks[2].pos.y = pos.y + 1;
    
    blocks[3].pos.x = pos.x + 1;
    blocks[3].pos.y = pos.y + 1;
    
    return ptr;
}
