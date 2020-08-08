CC=gcc
CFLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11


run: clean compile exec

compile: game snake

game: main.c snake.o vector2.o common.o snake_segment.o
	$(CC) main.c $(CFLAGS) -o game snake.o vector2.o common.o snake_segment.o

snake: snake.c
	$(CC) -c snake.c

vector2: vector2.c
	$(CC) -c vector2.c

common: common.c
	$(CC) -c common.c

snake_segment: snake_segment.c
	$(CC) -c snake_segment.c

exec: game
	./game

clean:
	rm -f game *.o