CC=gcc
CFLAGS=-c -Wall

staticLib: libwcarray.c
	$(CC) $(CFLAGS) libwcarray.c
	ar cr libwcarray.a libwcarray.o

sharedLib: libwcarray.c
	$(CC) $(CFLAGS) -fPIC libwcarray.c
	$(CC) -shared -o libwcarray.so libwcarray.o

all:
	make staticLib
	make sharedLib

clean:
	rm -f *.o *.a *.so

