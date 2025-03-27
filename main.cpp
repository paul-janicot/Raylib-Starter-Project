#include "raylib.h"
#include <iostream>
#include <random>

using namespace std;


int roll(int minNum, int maxNum)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> distrib(minNum, maxNum);
    return distrib(gen);
}

unsigned char rollColor() {
    return static_cast<unsigned char>(roll(0, 255));
}


Color ChangeColor() 
{
    return Color{rollColor(),rollColor(),rollColor(),255};
}



int main() {

    
    cout << "Hello World" << endl;

    int x = 300;
    int y = 500;

    InitWindow(x, y, "Amazing game");
    SetTargetFPS(60);

    //Init

    float ballX = 20;
    float ballY = 20;

    float radius = 20;

    int movementX = 10;
    int movementY = 10;

    vector<Vector2> hitPositions;

    Color color = RED;




    while (!WindowShouldClose()) {
        //Update

        ballX += movementX;
        ballY += movementY;

        if (ballX <= radius || ballX >= x - radius) {
            movementX *= -1;
            color = ChangeColor();
            
            hitPositions.push_back(Vector2{ ballX,ballY });
        }
         if (ballY<= radius || ballY >= y - radius) {
            movementY *= -1;
            hitPositions.push_back(Vector2{ ballX,ballY });
            color = ChangeColor();

          
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);

        //Draw

        DrawCircle(ballX,ballY,radius,color);
        for (Vector2 hitPosition: hitPositions) {
            DrawText("Boing", hitPosition.x, hitPosition.y, 10, color);
        }
       

        EndDrawing();
    }

    CloseWindow();
    return 0;
}