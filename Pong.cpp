#include "raylib.h"
#include <iostream>

using namespace std;

int main() {
//-----Const---------------
    const int x = 800;
    const int y = 500;
    
    const int margeY = 50;

    const float radius = 20;

    const int sizeOfPadel = 100;
    const int widthOfPadel = 10;

    const int padelSpeed = 10;

    

    const Vector2 scorePosition1{ x *0.30, y / 10 };
    const Vector2 scorePosition2{ x*0.70, y / 10 };
    
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

    int score1 = 0;
    int score2 = 0;

//----------------------------



    InitWindow(x, y, "Amazing game");
    SetTargetFPS(60);


    //Init

    InitAudioDevice();
    Music lvlMusic = LoadMusicStream("Sounds/Bloopin.mp3");
    PlayMusicStream(lvlMusic);
    bool pause = false;

    Font ft = LoadFont("resources/fonts/alagard.png");
    Image img = LoadImage("resources/images/background.png");
    Texture2D texture = LoadTextureFromImage(img);      // Image converted to texture, uploaded to GPU memory (VRAM)
    UnloadImage(img);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM


    while (!WindowShouldClose()) {
        //Update

        if (IsKeyDown('W') &&(padelPositionY1 >= margeY)){
            padelPositionY1 -= padelSpeed;
        }
        else if (IsKeyDown('S') && padelPositionY1 <= y-margeY-sizeOfPadel){
            padelPositionY1 += padelSpeed;
        }
        if (IsKeyDown(KEY_UP) && (padelPositionY2 >= margeY)) 
        {
            padelPositionY2 -= padelSpeed;
        }
        if (IsKeyDown(KEY_DOWN) && (padelPositionY2 <= y - margeY - sizeOfPadel))
        {
            padelPositionY2 += padelSpeed;
        }

        UpdateMusicStream(lvlMusic);
        if (IsKeyPressed(KEY_SPACE)) {
            pause = !pause;
            if (pause) StopMusicStream(lvlMusic);
            else ResumeMusicStream(lvlMusic);
        }



        // Mise à jour de la position de la balle
        ballX += movementX;
        ballY += movementY;

        // Rebond sur les murs haut et bas
        if (ballY <= radius || ballY >= y - radius) {
            movementY *= -1;
        }

        // Collision avec la raquette gauche (padel 1)
        if ((ballX - radius <= padelPositionX1 + widthOfPadel) &&
            (ballY >= padelPositionY1 && ballY <= padelPositionY1 + sizeOfPadel)) {
            movementX *= -1;
        }

        // Collision avec la raquette droite (padel 2)
        if ((ballX + radius >= padelPositionX2) &&  // Vérifie si la balle touche le bord gauche de la raquette 2
            (ballY >= padelPositionY2 && ballY <= padelPositionY2 + sizeOfPadel)) {
            movementX *= -1;
        }

        if (ballX <= 0) {
            score2 += 1;
            ballX = x * 0.75;
        }
        if (ballX >= x) {
            score1 += 1;
            ballX = x / 4;
        }

       
        

        BeginDrawing();
        

        ClearBackground(BLACK);

        //Draw
        DrawTexture(texture, 0, 0, WHITE);
        DrawRectangle(padelPositionX1, padelPositionY1, widthOfPadel, sizeOfPadel, WHITE);
        DrawRectangle(padelPositionX2, padelPositionY2, widthOfPadel, sizeOfPadel, WHITE);
        DrawCircle(ballX, ballY, radius, WHITE);
        DrawTextEx(ft, TextFormat("%i", score1), scorePosition1, 40, 5, WHITE);
        DrawTextEx(ft, TextFormat("%i", score2), scorePosition2, 40, 5, WHITE);
        DrawLine(x / 2, 0, x / 2, y, WHITE);

       

        EndDrawing();
    }

    UnloadMusicStream(lvlMusic);
    CloseWindow();
    return 0;
}