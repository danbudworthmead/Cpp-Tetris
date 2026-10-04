#include "Grid.h"

#include <functional>

#include "Tetromino.h"
#include "TetrominoFactory.h"

Grid::Grid(const int width, const int height) :
    width_(width),
    height_(height),
    spawn_point_({ width / 2, 0 }),
    grid_(width * height)
{
    tetromino_ = TetrominoFactory::Create(spawn_point_[0], spawn_point_[1]);
}

Grid::~Grid() = default;

bool Grid::IsOccupied(const int x, const int y) const
{
    if (x < 0 || x >= width_ || y < 0 || y >= height_)
    {
        return true;
    }
    
    return grid_[GetIndex(x, y)].has_value();
}

void Grid::SetBlock(const int x, const int y, const Block& block)
{
    if (x < 0 || x >= width_ || y < 0 || y >= height_)
    {
        on_game_over_();
        return;
    }
    
    grid_[GetIndex(x, y)] = block;
}

const std::array<Block, 4>& Grid::GetTetrominoBlocks() const
{
    return tetromino_->GetBlocks();
}

void Grid::OnGameOver(const std::function<void()>& on_game_over)
{
    on_game_over_ = on_game_over;
}

size_t Grid::GetIndex(const int x, const int y) const
{
    return y * width_ + x;
}

void Grid::Update()
{
    if (tetromino_->CanMoveDown(*this))
    {
        tetromino_->MoveDown();
    }
    else
    {
        LockInPlace(*tetromino_);
        tetromino_ = TetrominoFactory::Create(spawn_point_[0], spawn_point_[1]);
        
        if (on_game_over_ != nullptr)
        {
            // check we are not overlapping any locked in blocks
            for (const auto& block : tetromino_->GetBlocks())
            {
                if (IsOccupied(block.x, block.y))
                {
                    on_game_over_();
                    return;
                }
            }
            
            // check for game over if a callback has been set
            if (!tetromino_->CanMoveDown(*this))
            {
                on_game_over_();
            }
        }
    }
}

void Grid::LockInPlace(const Tetromino& tetromino)
{
    const std::array<Block, 4>& blocks = tetromino.GetBlocks();
    for (const Block& block : blocks)
    {
        SetBlock(block.x, block.y, block);
    }
}
