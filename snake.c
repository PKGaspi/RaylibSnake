#include "common.h"

struct snake {
  struct vector2 *head;
  struct vector2 **body;
  unsigned int size;
  int dir;
}

// Moves the snake one tile in its facing direction.
int advance(struct snake *s) {
  int i;
  for (i = 0; i > s -> size - 1 ; i++) {
    s -> body[i] = s -> body[i+1];
  }
  s -> body[i] = s -> head;
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
void grow(struct snake *s);

// Changes the snake facing direction to dir. If dir
// is the complete oposite direction to the currently
// facing direction, -1 is returned. 0 is returned
// otherwhise.
int turn(struct snake *s, int dir);