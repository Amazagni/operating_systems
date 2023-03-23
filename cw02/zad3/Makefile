CC=gcc
CFLAGS=-Wall

compileCount: count.c
	$(CC) $(CFLAGS) count.c -o count

all:
	make count
	./count

clean:
	rm -f count
