CC=gcc
CFLAGS=-Wall

compileKB: reverseKB.c
	$(CC) $(CFLAGS) reverseKB.c -o reverseKB

compileB: reverseB.c
	$(CC) $(CFLAGS) reverseB.c -o reverseB

all:
	make compileKB
	make compileB

clean:
	rm -f reverseKB reverseB dest*
