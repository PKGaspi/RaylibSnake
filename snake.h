#include "snake_segment.h"

struct snake {
  struct snake_segment *head;
  struct snake_segment **body;
  unsigned int size;
  int dir;
  float tile_progress;
};

struct snake *snake_create(int x, int y);

// Moves the snake in this tile.
void snake_move(struct snake *s, float delta);

// Moves the snake one tile in its facing direction.
int snake_advance(struct snake *s);

// Enlarges the snake size by one.
void snake_grow(struct snake *s);

// Changes the snake facing direction to dir. If dir
// is the complete oposite direction to the currently
// facing direction, -1 is returned. 0 is returned
// otherwhise.
int snake_turn(struct snake *s, int dir);

// Returns 1 if the head and any body position is equal.
// Returns 0 otherwhise.
int snake_self_collided(struct snake *s);

float snake_get_speed(struct snake *s);

void snake_draw(struct snake *s, int tile_width, int tile_height);

void snake_free(struct snake *s);

