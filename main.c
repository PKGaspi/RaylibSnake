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
#include <stdlib.h>

struct fruit *fruit_random_create(struct snake *s, int fieldWidth, int fieldHeight);

void grid_draw(int fieldWidth, int fieldHeight, int tileWidth, int tileHeight, Color color);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    const char *SCORE_TEXT = "Score: %i";
    const char *GAME_OVER_TEXT = "Game over";
    const char *VICTORY_TEXT = "Congratulations! You won!";
    const char *RETRY_TEXT = "Press Enter to start a new game";
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

    struct snake *player_snake = NULL;
    struct fruit *fruit = NULL;
    
    int game_over = -1;
    int score = 0;


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Update your variables here
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
                    fruit = NULL;
                    if (player_snake -> size + 1 >= fieldHeight * fieldWidth) {
                        game_over = 2;
                    }
                    else {
                        fruit = fruit_random_create(player_snake, fieldWidth, fieldHeight);
                    }
                }
            }
        }
        else {
            if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
                if (player_snake) snake_free(player_snake);
                if (fruit) fruit_free(fruit);
                player_snake = snake_create(fieldWidth / 2, fieldHeight / 2, 3);
                fruit = fruit_random_create(player_snake, fieldWidth, fieldHeight);
                
                game_over = 0;
                score = 0;
            }
        }   
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();{

            ClearBackground(BLACK);

            grid_draw(fieldWidth, fieldHeight, tileWidth, tileHeight, GRAY);
            
            if (player_snake) snake_draw(player_snake, tileWidth, tileHeight, fieldWidth, fieldHeight, .75);
            if (fruit) fruit_draw(fruit, tileWidth, tileHeight, tileWidth / 3);

            // Texts.
            
            // Points.
            if (game_over >= 0) {
                const char * score_text = TextFormat(SCORE_TEXT, score);
                DrawText(score_text, screenWidth / 2 - MeasureText(score_text, FONT_SIZE) / 2, 0, FONT_SIZE, MAGENTA);  
            }
            // Game over or victory text.
            switch (game_over) {
                case 1: 
                DrawText(GAME_OVER_TEXT, screenWidth / 2 - MeasureText(GAME_OVER_TEXT, FONT_SIZE) / 2, FONT_SIZE + 2, FONT_SIZE, MAGENTA);
                break;
                case 2:
                DrawText(VICTORY_TEXT, screenWidth / 2 - MeasureText(VICTORY_TEXT, FONT_SIZE) / 2, FONT_SIZE + 2, FONT_SIZE, MAGENTA);
                break;
            }
            // New game text.
            if (game_over) {
                DrawText(RETRY_TEXT, screenWidth / 2 - MeasureText(RETRY_TEXT, FONT_SIZE) / 2, (FONT_SIZE + 2) * 2, FONT_SIZE, MAGENTA);    
            }
        }
        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    if (player_snake) snake_free(player_snake);
    if (fruit) fruit_free(fruit);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

struct fruit *fruit_random_create(struct snake *s, int fieldWidth, int fieldHeight) {
    struct vector2 *v = vector2_create(GetRandomValue(0, fieldWidth - 1), GetRandomValue(0, fieldHeight - 1));
    int i;
    if (vector2_equals(v, s -> head -> pos)) {
        return fruit_random_create(s, fieldWidth, fieldHeight);
    }
    for (i = 0; i < s -> size; i++) {
        if (vector2_equals(v, s -> body[i] -> pos)) {
            return fruit_random_create(s, fieldWidth, fieldHeight);
        }
    }
    struct fruit *f = fruit_create(v -> x, v -> y);
    return f;
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