#include <chrono>
#include <iostream>
#include <thread>
#include <string>
#include <array>
#include <conio.h>

#include <lm2/vectors/lm2_vector2.h>

#include "Block.h"
#include "Grid.h"

using namespace std::chrono_literals;

constexpr int kWidth = 10;
constexpr int kHeight = 20;

namespace
{
    size_t GetIndex(const int x, const int y)
    {
        return y * (kWidth + 1) + x;
    }

    enum class Keys
    {
        ESCAPE = 27,
        UP = 72,
        LEFT = 75,
        RIGHT = 77,
        DOWN = 80,
    };
}

int main() 
{
    Grid grid(kWidth, kHeight);
    
    bool game_lost = false;
    grid.OnGameOver([&]
    {
        game_lost = true;
    });
    
    std::string buffer;
    buffer.resize((kWidth + 1) * kHeight);
    
    while (game_lost == false)
    {
        std::this_thread::sleep_for(0.1s);
        
        int key = 0;
        
        lm2_v2_i8 input;
        input.x = 0;
        input.y = 0;
        
        if (_kbhit())
        {
            key = _getch();

            std::cout << key << std::endl;

            switch (static_cast<Keys>(key))
            {
            case Keys::ESCAPE:
                {
                    game_lost = true;
                }
                break;
            case Keys::UP:
                {
                    input.x = 0;
                    input.y = 1;
                }
                break;
            case Keys::LEFT:
                {
                    input.x = -1;
                    input.y = 0;
                }
                break;
            case Keys::RIGHT:
                {
                    input.x = 1;
                    input.y = 0;
                }
                break;
            case Keys::DOWN:
                {
                    input.x = 0;
                    input.y = -1;
                }
                break;
            }
        }
    
        grid.Update(input);
        
        // clear the grid
        std::system("cls");
        
        // put the grid into the buffer
        for (int y = 0; y < kHeight; ++y)
        {
            for (int x = 0; x < kWidth; ++x)
            {
                buffer[GetIndex(x, y)] = grid.IsOccupied(x, y) ? '#' : ' '; 
            }
            buffer[GetIndex(kWidth, y)] = '\n';
        }
        
        // put the tetromino into the buffer
        const std::array<Block, 4>& blocks = grid.GetTetrominoBlocks();
        for (const Block& block : blocks)
        {
            buffer[GetIndex(block.x, block.y)] = '#';
        }
        
        std::cout << buffer;
    }
    
    std::system("cls");
    
    if (game_lost)
    {
        std::cout << "YOU LOST!" << std::endl;
        std::system("pause");
    }
    
    return 0;
}
