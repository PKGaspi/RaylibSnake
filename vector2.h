#ifndef VECTOR2_H
#define VECTOR2_H

struct vector2 {
  int x;
  int y;
};

#endif

struct vector2 *vector2_create(int x, int y);

int vector2_get_dir(struct vector2 *v);

int vector2_equals(struct vector2 *v1, struct vector2 *v2);