#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "color.h"
#include <raylib.h>

class Block{
    public:      
        int id;
        std::map<int, std::vector<Position>> cells;
        Block();
        void Draw(int offsetX, int offsetY);
        void Move(int row, int col);
        void Rotate();
        void UndoRotation();
        std::vector<Position> getCellPositions();
        

    private:
        int cellSize;
        int rotationState;
        int rowOffset;
        int colOffset;
        std::vector<Color> colors;

};