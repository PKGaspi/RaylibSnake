#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "snake.h"
#include "raylib.h"

float const SNAKE_BASE_SPEED = 3; // Tiles per second.
float const SNAKE_BONUS_SPEED = .2; // Tiles per second * size.

struct snake *snake_create(int x, int y, int size) {

  struct snake *s = malloc(sizeof(struct snake));
  if (!s) return NULL;

  s -> size = size;
  s -> head = snake_segment_create(x, y, DIR_RIGHT, GREEN);
  s -> body = malloc(sizeof(struct snake_segment*) * (s -> size));

  int i;
  for (i = 0; i < s -> size; i++) {
    s -> body[i] = snake_segment_create(x - (i+1), y, DIR_RIGHT, LIME);
  }
  s -> dir = DIR_RIGHT;
  s -> turn_dir = s -> dir;
  s -> tile_progress = 0;
  return s;
}

int snake_move(struct snake *s, float delta) {
  s -> tile_progress += delta * snake_get_speed(s);
  if (s -> tile_progress >= 1) {
    return 1;
  }
  return 0;
}

// Moves the snake one tile in its facing direction.
int snake_advance(struct snake *s) {
  int i;
  for (i = s -> size - 1; i > 0; i--) {
    s -> body[i] -> pos -> x = s -> body[i-1] -> pos -> x;
    s -> body[i] -> pos -> y = s -> body[i-1] -> pos -> y;
    s -> body[i] -> dir = s -> body[i-1] -> dir;
  }
  if (s -> size > 0) {
    s -> body[0] -> pos -> x = s -> head -> pos -> x;
    s -> body[0] -> pos -> y = s -> head -> pos -> y;
    s -> body[0] -> dir = s -> head -> dir;
  }

  switch (s -> dir) {
    case DIR_UP: s -> head -> pos -> y--; break;
    case DIR_DOWN: s -> head -> pos -> y++; break;
    case DIR_RIGHT: s -> head -> pos -> x++; break;
    case DIR_LEFT: s -> head -> pos -> x--; break;
    default: return -1;
  }
  s -> tile_progress -= 1;
  s -> dir = s -> turn_dir;
  s -> head -> dir = s -> turn_dir;
  return 0;
}

// Enlarges the snake size by one.
void snake_grow(struct snake *s) {
  struct snake_segment **tmp = realloc(s -> body, sizeof(struct snake_segment*) * (s -> size + 1));
  if (tmp) {
    switch (tmp[s -> size - 1] -> dir) {
      case DIR_UP: 
        tmp[s -> size] = snake_segment_create(tmp[s -> size - 1] -> pos -> x, tmp[s -> size - 1] -> pos -> y + 1, tmp[s -> size - 1] -> dir, tmp[s -> size - 1] -> color);
        break;
      case DIR_DOWN: 
        tmp[s -> size] = snake_segment_create(tmp[s -> size - 1] -> pos -> x, tmp[s -> size - 1] -> pos -> y - 1, tmp[s -> size - 1] -> dir, tmp[s -> size - 1] -> color);
        break;
      case DIR_LEFT: 
        tmp[s -> size] = snake_segment_create(tmp[s -> size - 1] -> pos -> x + 1, tmp[s -> size - 1] -> pos -> y, tmp[s -> size - 1] -> dir, tmp[s -> size - 1] -> color);
        break;
      case DIR_RIGHT: 
        tmp[s -> size] = snake_segment_create(tmp[s -> size - 1] -> pos -> x - 1, tmp[s -> size - 1] -> pos -> y, tmp[s -> size - 1] -> dir, tmp[s -> size - 1] -> color);
        break;
    }
    
    s -> size++;
    s -> body = tmp;
  }
}

// Changes the snake facing direction to dir. If dir
// is the complete oposite direction to the currently
// facing direction or the same, -1 is returned. 
// 0 is returned otherwhise.
int snake_turn(struct snake *s, int dir) {
  if ((dir == s -> dir) || 
    (dir == DIR_LEFT && s -> dir == DIR_RIGHT) ||
    (dir == DIR_RIGHT && s -> dir == DIR_LEFT) ||
    (dir == DIR_UP && s -> dir == DIR_DOWN) ||
    (dir == DIR_DOWN && s -> dir == DIR_UP))  {
    return -1;
  }
  s -> turn_dir = dir;
  return 0;
}

int snake_self_collided(struct snake *s) {
  int i;
  for (i = 0; i < s -> size; i++) {
    if (vector2_equals(s -> body[i] -> pos, s -> head -> pos)) return 1;
  }
  return 0;
}

float snake_get_speed(struct snake *s) {
  return s -> size * SNAKE_BONUS_SPEED + SNAKE_BASE_SPEED;
}

void snake_draw(struct snake *s, int tile_width, int tile_height, int field_width, int field_height, float size_multiplier) {
  int i;
  for (i = 0; i < s -> size; i++) {
    snake_segment_draw(s -> body[i], s -> tile_progress, tile_width, tile_height, field_width, field_height, size_multiplier);
  }
  snake_segment_draw(s -> head, s -> tile_progress, tile_width, tile_height, field_width, field_height, size_multiplier);
}

void snake_free(struct snake *s) {
  snake_segment_free(s -> head);
  int i;
  for (i = 0; i < s -> size; i++) {
    snake_segment_free(s -> body[i]);
  }
  free(s -> body);
  free(s);
}