#include "raylib.h"
#include <iostream>

using namespace std;

int main() {
//-----Const---------------
    const int x = 500;
    const int y = 500;
    
    const int margeY = 50;

    const float radius = 20;

    const int sizeOfPadel = 100;
    const int widthOfPadel = 10;

    
//--------Variables------------------
    int padelPositionX1 = 50;
    int padelPositionY1 = 50;

    int padelPositionX2 = x-50;
    int padelPositionY2 = 50;


    int bottomYPadel1 = padelPositionY1 + sizeOfPadel;
    int UpYPadel1 = padelPositionY1;

    float ballX = 200;
    float ballY = 100;

    int movementX = 8;
    int movementY = 8;

//----------------------------



    InitWindow(x, y, "Amazing game");
    SetTargetFPS(60);


    //Init



    while (!WindowShouldClose()) {
        //Update

        if (IsKeyDown('W') &&(padelPositionY1 >= margeY)){
            padelPositionY1 -= 10;
        }
        else if (IsKeyDown('S') && padelPositionY1 <= y-margeY-sizeOfPadel){
            padelPositionY1 += 10;
        }


        ballX += movementX;
        ballY += movementY;

        if (ballX <= radius || ballX >= x - radius) {
            movementX *= -1;
      

           
        }
        if (ballY <= radius || ballY >= y - radius) {
            movementY *= -1;
        }
        else if ((ballX <= padelPositionX1+widthOfPadel + radius) && ((ballY >= padelPositionY1) && (ballY >= padelPositionY1-sizeOfPadel))){
            movementX *= -1;
        }
        

        BeginDrawing();
        ClearBackground(BLACK);

        //Draw
        DrawRectangle(padelPositionX1, padelPositionY1, widthOfPadel, sizeOfPadel, WHITE);
        DrawRectangle(padelPositionX2, padelPositionY2, widthOfPadel, sizeOfPadel, WHITE);
        DrawCircle(ballX, ballY, radius, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}