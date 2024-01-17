#pragma once
#include "grid.h"
#include "blocks.cpp"
#include <vector>

class Game{
    public:
        bool gameOver;
        int score;
        Game();
        void Draw();
        void HandleInput();
        void MoveBlockLeft();
        void MoveBlockRight();
        void MoveBlockDown();
        bool BlockFits();

    private:
        Grid grid;
        std::vector<Block> blocks;
        Block currentBlock;
        Block nextBlock;
        std::vector<Block> GetAllBlocks();
        Block GetRandomBlock();
        bool IsBlockOutside();
        void RotateBlock();
        void LockBlock();
        void Reset();
        void UpdateScore(int linesCleared, int moveDownPoints);


};