CLFAGS =-g -Wall -Werror
CC=gcc
.PHONY: all clean

all: main

main: main.c fun.h fun.c
	$(CC) $(CFLAGS) fun.c main.c -o main

clean:
	-rm -f main
