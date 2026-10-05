#pragma once
#include <array>
#include <functional>
#include <memory>
#include <vector>
#include <optional>
#include <span>

#include "Block.h"

#include "lm2/vectors/lm2_vector2.h"

class Tetromino;

class Grid
{
public:
    Grid(int width, int height);
    ~Grid();

    void Update(lm2_v2_i8 input);

    void SetBlock(const Block& block);
    [[nodiscard]] bool IsOccupied(int x, int y) const;
    [[nodiscard]] const std::array<Block, 4>& GetTetrominoBlocks() const;
    
    void OnGameOver(std::function<void()> on_game_over);
    int GetScore() const;

private:
    int GetIndex(int x, int y) const;
    
    int width_;
    int height_;
    int score_;
    
    lm2_v2_i8 spawn_point_;
    
    /**
     * accessed by grid [y * width_ + x] so rows are stored sequentially.
     * More optimal in memory when iterating
     */
    std::vector<std::optional<Block>> grid_;

    /**
     * the current tetromino in play
     */
    std::unique_ptr<Tetromino> tetromino_;
    
    std::function<void()> on_game_over_;

    void LockInPlace(const Tetromino& tetromino);
    static bool IsRowComplete(std::span<std::optional<Block>> row);
    void ClearRow(std::span<std::optional<Block>> row);
    void CheckRows(const Tetromino& tetromino);
    std::span<std::optional<Block>> GetRow(const int row_index);
};
