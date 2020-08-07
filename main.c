/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples in Notepad++, provided with default raylib installer package, 
*   just press F6 and run [raylib_compile_execute] script, it will compile and execute.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on [C:\raylib\raylib\examples] directory and
*   raylib official webpage: [www.raylib.com]
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2020 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <raylib.h>
#include "snake.h"
#include "vector2.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Snake");

    const unsigned int fieldWidth = 40;
    const unsigned int fieldHeight = 22;

    const unsigned int tileWidth = screenWidth / fieldWidth;
    const unsigned int tileHeight = screenHeight / fieldHeight;

    struct snake *player_snake = snake_create(3, 3);

    SetTargetFPS(10);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        snake_advance(player_snake);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

            DrawRectangle(player_snake -> head -> x * tileWidth, player_snake -> head -> y * tileHeight, tileWidth, tileHeight, WHITE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}