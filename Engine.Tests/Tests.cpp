#include <catch2/catch_test_macros.hpp>

#include "Tetromino.h"
#include "TetrominoFactory.h"

TEST_CASE("Tetromino Factory creates tetromino with 4 blocks")
{
    const std::unique_ptr<Tetromino> tetromino = TetrominoFactory::Create({0, 0});
    REQUIRE(tetromino->GetBlocks().size() == 4);
}
