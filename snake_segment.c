#include "snake_segment.h"
#include "common.h"
#include "stdlib.h"

struct snake_segment *snake_segment_create(int x, int y, int dir, Color color) {
  struct snake_segment *sg = malloc(sizeof(struct snake_segment));
  sg -> pos = vector2_create(x, y);
  sg -> dir = dir;
  sg -> color = color;
  return sg;
}

void snake_segment_draw(struct snake_segment *sg, float offset, int tile_width, int tile_height) {

  float x_offset = 0, y_offset = 0;
  switch (sg -> dir) {
    case DIR_LEFT: x_offset = -offset; break;
    case DIR_RIGHT: x_offset = offset; break;
    case DIR_UP: y_offset = -offset; break;
    case DIR_DOWN: y_offset = offset; break;
  }
  DrawRectangle((sg -> pos -> x + x_offset) * tile_width, (sg -> pos -> y + y_offset) * tile_height, tile_width, tile_height, sg -> color);
        
}

void snake_segment_free(struct snake_segment *sg) {
  free(sg -> pos);
  free(sg);
}