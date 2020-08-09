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

void snake_segment_draw(struct snake_segment *sg, float offset, int tile_width, int tile_height, int field_width, int field_height, float tile_margin) {
  float x_offset = 0, y_offset = 0;
  switch (sg -> dir) {
    case DIR_LEFT: 
    x_offset = -offset;
    if (sg -> pos -> x <= 0)
        // Draw extra rectangle on the other side.
      DrawRectangle((field_width + x_offset) * tile_width +( tile_width - tile_width * tile_margin) / 2, (sg -> pos -> y + y_offset) * tile_height + (tile_height - tile_height * tile_margin) / 2, tile_width * tile_margin, tile_height * tile_margin, sg -> color);
    break;

    case DIR_RIGHT: 
    x_offset = offset; 
    if (sg -> pos -> x >= field_width - 1)
        // Draw extra rectangle on the other side.
      DrawRectangle((-1 + x_offset) * tile_width +( tile_width - tile_width * tile_margin) / 2, (sg -> pos -> y + y_offset) * tile_height + (tile_height - tile_height * tile_margin) / 2, tile_width * tile_margin, tile_height * tile_margin, sg -> color);
    break;

    case DIR_UP: 
    y_offset = -offset; 
    if (sg -> pos -> y <= 0)
        // Draw extra rectangle on the other side.
      DrawRectangle((sg -> pos -> x + x_offset) * tile_width +( tile_width - tile_width * tile_margin) / 2, (field_height + y_offset) * tile_height + (tile_height - tile_height * tile_margin) / 2, tile_width * tile_margin, tile_height * tile_margin, sg -> color);
    break;

    case DIR_DOWN: 
    y_offset = offset; 
    if (sg -> pos -> y >= field_height - 1)
        // Draw extra rectangle on the other side.
      DrawRectangle((sg -> pos -> x + x_offset) * tile_width +( tile_width - tile_width * tile_margin) / 2, (-1 + y_offset) * tile_height + (tile_height - tile_height * tile_margin) / 2, tile_width * tile_margin, tile_height * tile_margin, sg -> color);
    break;

  }
  DrawRectangle((sg -> pos -> x + x_offset) * tile_width +( tile_width - tile_width * tile_margin) / 2, (sg -> pos -> y + y_offset) * tile_height + (tile_height - tile_height * tile_margin) / 2, tile_width * tile_margin, tile_height * tile_margin, sg -> color);

}

void snake_segment_free(struct snake_segment *sg) {
  free(sg -> pos);
  free(sg);
}