#include "fruit.h"
#include <stdlib.h>


struct fruit *fruit_create(int x, int y) {

  struct fruit *f = malloc(sizeof(struct fruit));
  if (!f) return NULL;

  f -> pos = vector2_create(x, y);
  f -> color = RED;

  return f;
}

void fruit_draw(struct fruit *f, int tileWidth, int tileHeight, float radious) {
  DrawCircle(f -> pos -> x * tileWidth + tileWidth / 4, f -> pos -> y * tileHeight + tileHeight / 4, radious, f -> color);
}

void fruit_free(struct fruit *f) {
  free(f -> pos);
  free(f);
}