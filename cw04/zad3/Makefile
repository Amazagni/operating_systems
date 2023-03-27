CC=gcc
CFLAGS=-Wall

compile sender: sender.c
	$(CC) $(CFLAGS) sender.c -o sender

compile catcher: catcher.c
		$(CC) $(CFLAGS) catcher.c -o catcher

all:
	make compile sender
	make compile catcher

clean:
	rm -f sender catcher
