#include <raylib.h>
#include "snake.h"
#include "fruit.h"
#include "common.h"
#include <stdlib.h>
#include "main.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    const char *PAUSE_TEXT = "Game paused";
    const char *SCORE_TEXT = "Score: %i";
    const char *GAME_OVER_TEXT = "Game over";
    const char *VICTORY_TEXT = "Congratulations! You won!";
    const char *RETRY_TEXT = "Press Enter to start a new game";
    const int FONT_SIZE = 20;

    const int FIELD_WIDTH = 30;
    const int FIELD_HEIGHT = 20;

    const int TILE_WIDTH = 35;
    const int TILE_HEIGHT = 35;

    const int SCREEN_WIDTH = FIELD_WIDTH * TILE_WIDTH;
    const int SCREEN_HEIGHT = FIELD_HEIGHT * TILE_HEIGHT;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");

    struct snake *player_snake = NULL;
    struct fruit *fruit = NULL;
    
    int pause = 0;
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
        if (IsKeyPressed(KEY_P) && !game_over) pause = !pause;

        if (!game_over && !pause) {


            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) snake_turn(player_snake, DIR_DOWN);
            else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) snake_turn(player_snake, DIR_UP);
            else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) snake_turn(player_snake, DIR_RIGHT);
            else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) snake_turn(player_snake, DIR_LEFT);

            // Move the snake.
            if (snake_move(player_snake, GetFrameTime())) {

                while (player_snake -> tile_progress >= 1) { // This while is for low frame rate cases.
                    snake_advance(player_snake); // Advance one tile.
                

                    // Check if we went through a screen border. If so, appear at the other side.
                    if (player_snake -> head -> pos -> x < 0) player_snake -> head -> pos -> x = FIELD_WIDTH - 1;
                    else if (player_snake -> head -> pos -> x >= FIELD_WIDTH) player_snake -> head -> pos -> x = 0;
                    else if (player_snake -> head -> pos -> y < 0) player_snake -> head -> pos -> y = FIELD_HEIGHT - 1;
                    else if (player_snake -> head -> pos -> y >= FIELD_HEIGHT) player_snake -> head -> pos -> y = 0;


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
                        if (player_snake -> size + 1 >= FIELD_HEIGHT * FIELD_WIDTH) {
                            game_over = 2;
                        }
                        else {
                            fruit = fruit_random_create(player_snake, FIELD_WIDTH, FIELD_HEIGHT);
                        }
                    }
                }
            }
        }
        else {
            if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
                if (player_snake) snake_free(player_snake);
                if (fruit) fruit_free(fruit);
                player_snake = snake_random_create(2, FIELD_WIDTH, FIELD_HEIGHT, GREEN, LIME);
                fruit = fruit_random_create(player_snake, FIELD_WIDTH, FIELD_HEIGHT);
                
                game_over = 0;
                score = 0;
            }
        }   
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();{

            ClearBackground(DARKGRAY);

            grid_draw(FIELD_WIDTH, FIELD_HEIGHT, TILE_WIDTH, TILE_HEIGHT, BLACK);

            if (player_snake) snake_draw(player_snake, TILE_WIDTH, TILE_HEIGHT, FIELD_WIDTH, FIELD_HEIGHT, .75);
            if (fruit) fruit_draw(fruit, TILE_WIDTH, TILE_HEIGHT, TILE_WIDTH / 3.2);

            // Texts.
            
            // Pause.
            if (pause) DrawText(PAUSE_TEXT, SCREEN_WIDTH / 2 - MeasureText(PAUSE_TEXT, FONT_SIZE) / 2, (SCREEN_HEIGHT - FONT_SIZE) / 2, FONT_SIZE, MAGENTA);
            
            // Points.
            if (game_over >= 0) {
                const char * score_text = TextFormat(SCORE_TEXT, score);
                DrawText(score_text, SCREEN_WIDTH / 2 - MeasureText(score_text, FONT_SIZE) / 2, 0, FONT_SIZE, MAGENTA);  
            }
            // Game over or victory text.
            switch (game_over) {
                case 1: 
                DrawText(GAME_OVER_TEXT, SCREEN_WIDTH / 2 - MeasureText(GAME_OVER_TEXT, FONT_SIZE) / 2, FONT_SIZE + 2, FONT_SIZE, MAGENTA);
                break;
                case 2:
                DrawText(VICTORY_TEXT, SCREEN_WIDTH / 2 - MeasureText(VICTORY_TEXT, FONT_SIZE) / 2, FONT_SIZE + 2, FONT_SIZE, MAGENTA);
                break;
            }
            // New game text.
            if (game_over) {
                DrawText(RETRY_TEXT, SCREEN_WIDTH / 2 - MeasureText(RETRY_TEXT, FONT_SIZE) / 2, (FONT_SIZE + 2) * 2, FONT_SIZE, MAGENTA);    
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

struct snake *snake_random_create(int size, int FIELD_WIDTH, int FIELD_HEIGHT, Color head_color, Color body_color) {
    struct vector2 *v = vector2_create(GetRandomValue(0, FIELD_WIDTH - 1), GetRandomValue(0, FIELD_HEIGHT - 1));
    int dir = GetRandomValue(DIR_UP, DIR_RIGHT);
    struct snake *s = snake_create(v -> x, v -> y, size, dir, head_color, body_color);

    free(v);
    return s;
}

struct fruit *fruit_random_create(struct snake *s, int FIELD_WIDTH, int FIELD_HEIGHT) {
    struct vector2 *v = vector2_create(GetRandomValue(0, FIELD_WIDTH - 1), GetRandomValue(0, FIELD_HEIGHT - 1));
    int i;
    if (vector2_equals(v, s -> head -> pos)) {
        return fruit_random_create(s, FIELD_WIDTH, FIELD_HEIGHT);
    }
    for (i = 0; i < s -> size; i++) {
        if (vector2_equals(v, s -> body[i] -> pos)) {
            return fruit_random_create(s, FIELD_WIDTH, FIELD_HEIGHT);
        }
    }
    struct fruit *f = fruit_create(v -> x, v -> y);
    free(v);
    return f;
}

void grid_draw(int FIELD_WIDTH, int FIELD_HEIGHT, int TILE_WIDTH, int TILE_HEIGHT, Color color) {

    int i;
    for (i = 0; i < FIELD_WIDTH; i++) {
        DrawLine(i * TILE_WIDTH, 0, i * TILE_WIDTH, FIELD_HEIGHT * TILE_HEIGHT, color);
    }
    for (i = 0; i < FIELD_HEIGHT; i++) {
        DrawLine(0, i * TILE_HEIGHT, FIELD_WIDTH * TILE_WIDTH, i * TILE_HEIGHT, color);
    }

}