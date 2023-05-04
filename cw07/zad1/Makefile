CC=gcc
CFLAGS=-Wall

all:
	$(CC) $(CFLAGS) barber.c my_semaphore.c shared_mem.c queue.c -o barber

	$(CC) $(CFLAGS) client.c my_semaphore.c shared_mem.c queue.c -o client

	$(CC) $(CFLAGS) engine.c my_semaphore.c shared_mem.c queue.c -o engine
clean:
	rm -f barber client engine
