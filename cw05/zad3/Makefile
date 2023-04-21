CC=gcc
CFLAGS=-Wall

compile main: main.c
	$(CC) $(CFLAGS) main.c -o main

compile counter: counter.c
	$(CC) $(CFLAGS) counter.c -o counter

all:
	make compile main
	make compile counter

clean:
	rm -f main counter

