CLFAGS =-g -Wall -Werror
CC=gcc
.PHONY: clean

run: build
	./tto

build: main.c fun.h fun.c
	$(CC) $(CFLAGS) fun.c main.c -o tto

clean:
	-rm -f main
