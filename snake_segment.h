#include "raylib.h"
#include "vector2.h"

struct snake_segment {
  struct vector2 *pos;
  int dir;
  Color color;
};

struct snake_segment *snake_segment_create(int x, int y, int dir, Color color);

void snake_segment_draw(struct snake_segment *sg, float offset, int tile_width, int tile_height, int field_width, int field_height, float tile_margin);

void snake_segment_free(struct snake_segment *sg);