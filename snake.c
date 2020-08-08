#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "vector2.h"
#include "snake.h"


struct snake *snake_create(int x, int y) {
  struct snake *s = malloc(sizeof(struct snake));
  if (!s) return NULL;
  s -> head = vector2_create(x, y);
  s -> size = 10;
  s -> body = malloc(sizeof(struct vector2*) * (s -> size));
  int i;
  for (i = 0; i < s -> size; i++) {
    s -> body[i] = vector2_create(x, y);
  }
  s -> dir = DIR_RIGHT;
  return s;
}

// Moves the snake one tile in its facing direction.
int snake_advance(struct snake *s) {
  int i;
  for (i = 0; i < s -> size - 1; i++) {
    s -> body[i] -> x = s -> body[i+1] -> x;
    s -> body[i] -> y = s -> body[i+1] -> y;
  }
  if (s -> size > 0) {
    s -> body[i] -> x = s -> head -> x;
    s -> body[i] -> y = s -> head -> y;
  }
  switch (s -> dir) {
    case DIR_UP: s -> head -> y--; break;
    case DIR_DOWN: s -> head -> y++; break;
    case DIR_RIGHT: s -> head -> x++; break;
    case DIR_LEFT: s -> head -> x--; break;
    default: return -1;
  }
  return 0;
}

// Enlarges the snake size by one.
void snake_grow(struct snake *s);

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
  s -> dir = dir;
  return 0;
}

void snake_destroy(struct snake *s) {
  free(s -> head);
  int i;
  for (i = 0; i < s -> size + 1; i++) {
    free(s -> body[i]);
  }
  free(s -> body);
  free(s);
}