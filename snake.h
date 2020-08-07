struct snake;

// Moves the snake one tile in its facing direction.
int advance(struct snake s);

// Enlarges the snake size by one.
void grow(struct snake s);

// Changes the snake facing direction to dir. If dir
// is the complete oposite direction to the currently
// facing direction, -1 is returned. 0 is returned
// otherwhise.
int turn(struct snake s, int dir);