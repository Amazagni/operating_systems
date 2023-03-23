CC=gcc
CFLAGS=-c -Wall
ZAD1=../zad1/
LIB=libwcarray
MAIN=main
EXEC=exec
staticLib: $(ZAD1)$(LIB).c
	$(CC) $(CFLAGS) $(ZAD1)$(LIB).c
	ar cr $(LIB).a $(LIB).o

sharedLib: $(ZAD1)$(LIB).c
	$(CC) $(CFLAGS) -fPIC $(ZAD1)$(LIB).c
	$(CC) -shared -o $(LIB).so $(LIB).o

compileStatic: $(MAIN).c
	make staticLib
	$(CC) -Wall $(MAIN).c -o $(EXEC) -L. $(LIB).a

compileShared: $(MAIN).c
	make sharedLib
	$(CC) -Wall $(MAIN).c -o $(EXEC) -L. $(LIB).so

compileDynamic: $(MAIN)Dynamic.c
	make sharedLib
	$(CC) -Wall $(MAIN)Dynamic.c -o $(EXEC)

runStatic:
	make compileStatic
	./$(EXEC)

runShared:
	make compileShared
	LD_LIBRARY_PATH=. ./$(EXEC)

runDynamic:
	make compileDynamic
	LD_LIBRARY_PATH=. ./$(EXEC)

clean:
	rm -f *.o *.a *.so exec