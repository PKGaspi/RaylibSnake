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
#include "fruit.h"
#include "common.h"

void grid_draw(int fieldWidth, int fieldHeight, int tileWidth, int tileHeight, Color color);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    const char *GAME_OVER_TEXT = "Game over";
    const int FONT_SIZE = 20;

    const int fieldWidth = 30;
    const int fieldHeight = 20;

    const int tileWidth = 20;
    const int tileHeight = 20;

    const int screenWidth = fieldWidth * tileWidth;
    const int screenHeight = fieldHeight * tileHeight;

    InitWindow(screenWidth, screenHeight, "Snake");

    const int snakeTileWidth = tileWidth - tileWidth / 10;
    const int snakeTileHeight = tileHeight - tileHeight / 10;

    struct snake *player_snake = snake_create(fieldWidth / 2, fieldHeight / 2, 10);
    struct fruit *fruit = fruit_create(GetRandomValue(0, fieldWidth-1), GetRandomValue(0, fieldHeight-1));
    
    int game_over = 0;
    int score = 0;


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        if (!game_over) {

            if (IsKeyDown(KEY_DOWN)) snake_turn(player_snake, DIR_DOWN);
            else if (IsKeyDown(KEY_UP)) snake_turn(player_snake, DIR_UP);
            else if (IsKeyDown(KEY_RIGHT)) snake_turn(player_snake, DIR_RIGHT);
            else if (IsKeyDown(KEY_LEFT)) snake_turn(player_snake, DIR_LEFT);

            // Move the snake.
            if (snake_move(player_snake, GetFrameTime())) {

                snake_advance(player_snake); // Advance one tile.

                // Check if we went through a screen border. If so, appear at the other side.
                if (player_snake -> head -> pos -> x < 0) player_snake -> head -> pos -> x = fieldWidth - 1;
                else if (player_snake -> head -> pos -> x >= fieldWidth) player_snake -> head -> pos -> x = 0;
                else if (player_snake -> head -> pos -> y < 0) player_snake -> head -> pos -> y = fieldHeight - 1;
                else if (player_snake -> head -> pos -> y >= fieldHeight) player_snake -> head -> pos -> y = 0;


                // Check if the snake dies.
                if (snake_self_collided(player_snake)) {
                    // Game over.
                    player_snake -> tile_progress = 0;
                    game_over = 1;
                }
                // Check if the snake ate a fruit.
                else if (vector2_equals(player_snake -> head -> pos, fruit -> pos)) {
                    // Eat fruit.
                    snake_grow(player_snake);
                    score++;
                    fruit_free(fruit);
                    fruit = fruit_create(GetRandomValue(0, fieldWidth-1), GetRandomValue(0, fieldHeight-1));
                }
            }
        }
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();{
        
            ClearBackground(BLACK);
    
            grid_draw(fieldWidth, fieldHeight, tileWidth, tileHeight, GRAY);
            snake_draw(player_snake, tileWidth, tileHeight, fieldWidth, fieldHeight, .75);
            fruit_draw(fruit, tileWidth, tileHeight, tileWidth / 3);
    
            if (game_over) DrawText(GAME_OVER_TEXT, screenWidth / 2 - MeasureText(GAME_OVER_TEXT, FONT_SIZE) / 2, 2, FONT_SIZE, MAGENTA);
        }
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

void grid_draw(int fieldWidth, int fieldHeight, int tileWidth, int tileHeight, Color color) {

    int i;
    for (i = 0; i < fieldWidth; i++) {
        DrawLine(i * tileWidth, 0, i * tileWidth, fieldHeight * tileHeight, color);
    }
    for (i = 0; i < fieldHeight; i++) {
        DrawLine(0, i * tileHeight, fieldWidth * tileWidth, i * tileHeight, color);
    }

}