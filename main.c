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
#include "common.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    const int fieldWidth = 40;
    const int fieldHeight = 22;

    const int tileWidth = 20;
    const int tileHeight = 20;

    const int screenWidth = fieldWidth * tileWidth;
    const int screenHeight = fieldHeight * tileHeight;

    InitWindow(screenWidth, screenHeight, "Snake");

    const int snakeTileWidth = tileWidth - tileWidth / 10;
    const int snakeTileHeight = tileHeight - tileHeight / 10;

    struct snake *player_snake = snake_create(10, 10);
    int game_over = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        if (!game_over) {

            if (IsKeyPressed(KEY_DOWN)) snake_turn(player_snake, DIR_DOWN);
            else if (IsKeyPressed(KEY_UP)) snake_turn(player_snake, DIR_UP);
            else if (IsKeyPressed(KEY_RIGHT)) snake_turn(player_snake, DIR_RIGHT);
            else if (IsKeyPressed(KEY_LEFT)) snake_turn(player_snake, DIR_LEFT);

            // Move the snake.
            if (snake_move(player_snake, GetFrameTime())) {
                snake_advance(player_snake);
            }

            // Check if we went through a screen border. If so, appear at the other side.
            switch (player_snake -> dir) {
                case DIR_LEFT:
                if (player_snake -> head -> pos -> x < 0) player_snake -> head -> pos -> x = fieldWidth - 1;
                break;
                case DIR_RIGHT:
                if (player_snake -> head -> pos -> x > fieldWidth) player_snake -> head -> pos -> x = 0;
                break;
                case DIR_UP:
                if (player_snake -> head -> pos -> y < 0) player_snake -> head -> pos -> y = fieldHeight - 1;
                break;
                case DIR_DOWN:
                if (player_snake -> head -> pos -> y > fieldHeight) player_snake -> head -> pos -> y = 0;
                break;
            }

            if (snake_self_collided(player_snake)) {
                // Game over.
                player_snake -> tile_progress = 0;
                game_over = 1;
            }
        }
        // Check collision with myself.
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        snake_draw(player_snake, tileWidth, tileHeight, .5);

        if (game_over) DrawText("Booooooooh! You just lost the game ;)", 190, 200, 20, GRAY);

        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    snake_free(player_snake);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}