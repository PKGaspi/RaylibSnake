

struct snake *snake_random_create(int size, int fieldWidth, int fieldHeight, Color head_color, Color body_color);

struct fruit *fruit_random_create(struct snake *s, int fieldWidth, int fieldHeight);

void grid_draw(int fieldWidth, int fieldHeight, int tileWidth, int tileHeight, Color color);