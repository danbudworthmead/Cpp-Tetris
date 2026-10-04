#include "TetrominoFactory.h"

#include "Tetromino.h"

std::unique_ptr<Tetromino> TetrominoFactory::Create(const int x, const int y)
{
    auto ptr = std::make_unique<Tetromino>();
    auto& blocks = ptr->GetBlocks();
    
    blocks[0].x = x + 0;
    blocks[0].y = y + 0;
    
    blocks[1].x = x + 1;
    blocks[1].y = y + 0;
    
    blocks[2].x = x + 0;
    blocks[2].y = y + 1;
    
    blocks[3].x = x + 1;
    blocks[3].y = y + 1;
    
    return ptr;
}
