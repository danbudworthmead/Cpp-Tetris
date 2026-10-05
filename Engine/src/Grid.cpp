#include "Grid.h"

#include <algorithm>
#include <functional>
#include <set>
#include "Tetromino.h"
#include "TetrominoFactory.h"

Grid::Grid(const int width, const int height) :
    width_(width),
    height_(height),
    score_(0),
    grid_(width * height)
{
    spawn_point_.x = width / 2;
    spawn_point_.y = 0;
    tetromino_ = TetrominoFactory::Create(spawn_point_);
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

void Grid::SetBlock(const Block& block)
{
    if (block.pos.x < 0 || block.pos.x >= width_ || block.pos.y < 0 || block.pos.y >= height_)
    {
        on_game_over_();
        return;
    }
    
    grid_[GetIndex(block.pos.x, block.pos.y)] = block;
}

const std::array<Block, 4>& Grid::GetTetrominoBlocks() const
{
    return tetromino_->GetBlocks();
}

void Grid::OnGameOver(std::function<void()> on_game_over)
{
    on_game_over_ = std::move(on_game_over);
}

int Grid::GetScore() const
{
    return score_;
}

int Grid::GetIndex(const int x, const int y) const
{
    return y * width_ + x;
}

void Grid::Update(lm2_v2_i8 input)
{
    // sanitize input as blocks cannot move upward
    if (input.y > 0)
    {
        input.y = 0;
    }
    
    if (input.x != 0 || input.y != 0)
    {
        if (tetromino_->CanMove(*this, input))
        {
            tetromino_->Move(input);
            return;
        }
    }
    
    lm2_v2_i8 down;
    down.x = 0;
    down.y = -1;
    
    if (tetromino_->CanMove(*this, down))
    {
        tetromino_->Move(down);
    }
    else
    {
        LockInPlace(*tetromino_);
        CheckRows(*tetromino_);
        
        tetromino_ = TetrominoFactory::Create(spawn_point_);
        
        if (on_game_over_ != nullptr)
        {
            // check we are not overlapping any locked in blocks
            for (const auto& block : tetromino_->GetBlocks())
            {
                if (IsOccupied(block.pos.x, block.pos.y))
                {
                    on_game_over_();
                    return;
                }
            }
            
            // check for game over if a callback has been set
            if (!tetromino_->CanMove(*this, down))
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
        SetBlock(block);
    }
    
    score_++;
}

bool Grid::IsRowComplete(const std::span<std::optional<Block>> row)
{
    for (std::optional<Block> block : row)
    {
        if (block.has_value() == false)
        {
            return false;
        }
    }
    
    return true;
}

void Grid::ClearRow(const std::span<std::optional<Block>> row)
{
    const std::ptrdiff_t offset = row.data() - grid_.data();
    std::shift_right(grid_.begin(), grid_.begin() + offset + width_, width_);
    std::ranges::fill(GetRow(0), std::nullopt);
}

void Grid::CheckRows(const Tetromino& tetromino)
{
    const std::array<Block, 4>& blocks = tetromino.GetBlocks();
    std::set<int> row_indexes;
    for (const Block& block : blocks)
    {
        if (block.pos.y < 0 || block.pos.y >= height_)
        {
            return;
        }
        
        row_indexes.insert(block.pos.y);
    }
    
    for (auto iter = row_indexes.begin(); iter != row_indexes.end();)
    {
        const std::span<std::optional<Block>> row = GetRow(*iter);
        
        if (IsRowComplete(row))
        {
            ClearRow(row);
        }
        else
        {
            ++iter;
        }
    }
}

std::span<std::optional<Block>> Grid::GetRow(const int row_index)
{
    assert(row_index >= 0 && row_index < height_);
    
    const int offset = row_index * width_;
    return std::span(grid_).subspan(offset, width_);
}
