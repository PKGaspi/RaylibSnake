#include "vector2.h"
#include <raylib.h>

struct fruit {
  struct vector2 *pos;
  Color color;
};

struct fruit *fruit_create(int x, int y);

void fruit_draw(struct fruit *f, int tileWidth, int tileHeight, float radious);

void fruit_free(struct fruit *f);