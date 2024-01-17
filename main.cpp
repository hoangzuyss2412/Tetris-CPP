#include <iostream>
#include <raylib.h>
#include "game.h"
#include "color.h"

using namespace std;


double lastUpdateTime = 0;
bool EventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}

int main () {
    InitWindow(500, 620, "Wonderful Tetris Game!");

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Game game = Game();
    
    while(WindowShouldClose() == false){
        game.HandleInput();
        if(EventTriggered(0.2)){
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);

        // Display game over message once user lost
        if(game.gameOver){
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
        }

        // Display user's score
        DrawRectangleRounded({320, 55, 170, 60}, 0.2, 12, lightBlue);
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        // Display the nexte block
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.2, 12, lightBlue);
        
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}