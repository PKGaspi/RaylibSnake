CC=gcc
CFLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11


run: compile exec

compile: main.c
	$(CC) main.c $(CFLAGS) -o game

exec: game
	./game

clean:
	rm game