#include "common.h"
#include "cola.h"

struct vector2 {
  int x;
  int y;
}

struct vector2 *vector2_create(int x, int y) {
  struct vector2 *v = malloc(sizeof(struct vecto2));
  if (!v) return NULL;
  c -> x = x;
  c -> y = y;
  return v;
}

int get_dir(struct vector2 *v) {
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