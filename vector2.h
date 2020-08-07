struct vector2 {
  int x;
  int y;
};

struct vector2 *vector2_create(int x, int y);

int get_dir(struct vector2 *v);