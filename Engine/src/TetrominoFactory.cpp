#include "TetrominoFactory.h"

#include "Tetromino.h"

namespace
{
    constexpr std::array<std::pair<int8_t, int8_t>, 7> kShapes[] = {
        {
            {
                {0, 0},
               {1, 0},
               {0, 1},
               {1, 1},
            },
        },
        {
            {
                {0, 0},
               {1, 0},
               {2, 0},
               {3, 0},
            },
        },
        {
            {
                {0, 1},
               {1, 1},
               {2, 1},
               {1, 0},
            },
        },
        {
            {
                {0, 0},
               {1, 0},
               {1, 1},
               {1, 2},
            },
        },
        {
            {
                {0, 0},
               {1, 0},
               {0, 1},
               {0, 2},
            },
        },
        {
            {
                {0, 0},
               {1, 0},
               {1, 1},
               {2, 1},
            },
        },
        {
            {
                {0, 1},
               {1, 1},
               {1, 0},
               {2, 0},
            },
        },
    };
}

std::unique_ptr<Tetromino> TetrominoFactory::Create(const lm2_v2_i8& pos)
{
    auto tetromino = std::make_unique<Tetromino>();
    auto& blocks = tetromino->GetBlocks();

    const int random_shape_index = std::rand() % std::size(kShapes);
    const std::array<std::pair<int8_t, int8_t>, 7>& shape = kShapes[random_shape_index];
    
    blocks[0].pos.x = pos.x + shape[0].first;
    blocks[0].pos.y = pos.y + shape[0].second;
    
    blocks[1].pos.x = pos.x + shape[1].first;
    blocks[1].pos.y = pos.y + shape[1].second;
    
    blocks[2].pos.x = pos.x + shape[2].first;
    blocks[2].pos.y = pos.y + shape[2].second;
    
    blocks[3].pos.x = pos.x + shape[3].first;
    blocks[3].pos.y = pos.y + shape[3].second;
    
    return tetromino;
}
