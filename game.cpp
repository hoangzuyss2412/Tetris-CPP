#include "game.h"
#include <random>

Game::Game(){
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
}

Block Game::GetRandomBlock(){
    if(blocks.empty()){
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);  
    return block;
}

std::vector<Block> Game::GetAllBlocks(){
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw(){
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
        case 3:
            nextBlock.Draw(255, 290);
            break;
        case 4:
            nextBlock.Draw(255, 280);
            break;
        default:
            nextBlock.Draw(270, 270);
            break;
    }
}

void Game::MoveBlockLeft(){
    if(gameOver) return;

    currentBlock.Move(0, -1);
    if(IsBlockOutside() || (BlockFits() == false)){
        currentBlock.Move(0, 1);
    }
}
void Game::MoveBlockRight(){
    if(gameOver) return;

    currentBlock.Move(0, 1);
    if(IsBlockOutside() || (BlockFits() == false)){
        currentBlock.Move(0, -1);
    }
}

void Game::MoveBlockDown(){
    if(gameOver) return;

    currentBlock.Move(1,0);
    if(IsBlockOutside() || BlockFits() == false){
        currentBlock.Move(-1, 0);
        LockBlock();
    }

}

void Game::RotateBlock(){
    if(gameOver) return;
    
    currentBlock.Rotate();
    if(IsBlockOutside()){
        currentBlock.UndoRotation();
    }
}

bool Game::IsBlockOutside(){
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for(Position item: tiles){
        if(grid.IsCellOutside(item.row, item.col)){
            return true;
        }
    }

    return false;
}

void Game::HandleInput(){
    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed != 0){
        Reset();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    
    case KEY_RIGHT:
        MoveBlockRight();
        break;

    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0,1);
        break;

    case KEY_UP:
        RotateBlock();
        break;

    default:
        break;
    }
}

void Game::LockBlock(){
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for(Position item: tiles){
        grid.grid[item.row][item.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(BlockFits() == false){
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    UpdateScore(rowsCleared, 0);
}

bool Game::BlockFits(){
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for(Position item: tiles){
        if(grid.IsCellEmpty(item.row, item.col) == false){
            return false;
        }
    }
    return true;
}

void Game::Reset(){
    grid.Initialize();
    gameOver = false;
    score = 0;
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    
}

void Game::UpdateScore(int linesCleared, int moveDownPoints){
    switch(linesCleared){
        case 1:
            score += 100;
            break;
        case 2:
            score += 200;
            break;
        case 3:
            score += 500;
            break;
        default:
            break;
    }

    score += moveDownPoints;
}
