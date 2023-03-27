CC=gcc
CFLAGS=-Wall

compileFork: fork.c
	$(CC) $(CFLAGS) fork.c -o fork

compileExec: exec.c
	$(CC) $(FLAGS) exec.c -o exec

compileExecChild: execChild.c
	$(CC) $(FLAGS) execChild.c -o execChild

all:
	make compileFork
	make compileExec
	make compileExecChild
clean:
	rm -f fork exec execChild
