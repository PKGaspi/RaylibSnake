#include <stdlib.h>
#include "common.h"
#include "vector2.h"


struct vector2 *vector2_create(int x, int y) {
  struct vector2 *v = malloc(sizeof(struct vector2));
  if (!v) return NULL;
  v -> x = x;
  v -> y = y;
  return v;
}

int vector2_get_dir(struct vector2 *v) {
  if (v -> x == 0) {
    if (v -> y > 0) return DIR_DOWN;
    else if (v -> y < 0) return DIR_UP;
  }
  else if (v -> y == 0) {
    if (v -> x > 0) return DIR_RIGHT;
    else if (v -> x < 0) return DIR_LEFT;
  }

  return DIR_OTHER;
}