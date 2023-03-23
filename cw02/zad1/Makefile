CC=gcc
CFLAGS=-Wall

compileLib: mainLib.c
	$(CC) $(CFLAGS) mainLib.c -o mainLib

compileSys: mainSys.c
	$(CC) $(CFLAGS) mainSys.c -o mainSys

all:
	make compileLib
	make compileSys

clean:
	rm -f mainLib mainSys dest*
