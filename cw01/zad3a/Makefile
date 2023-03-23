CC=gcc
CFLAGS=-c -Wall
ZAD1=../zad1/
LIB=libwcarray
MAIN=main
EXEC=exec
TEST=echo init 500; echo count main.c; echo count mainDynamic.c; echo count Makefile; echo show 0; echo show 1; echo show 2; echo delete 0; echo delete 1; echo delete 2; echo destroy
RES=results_
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

testStatic:
	make compileStatic
	($(TEST)) | ./$(EXEC) >> $(RES)static.txt

preTestShared:
	($(TEST)) | ./$(EXEC) >> $(RES)shared.txt

testShared:
	make compileShared
	LD_LIBRARY_PATH=. make preTestShared

preTestDynamic:
	($(TEST)) | ./$(EXEC) >> $(RES)dynamic.txt

testDynamic:
	make compileDynamic
	LD_LIBRARY_PATH=. make preTestDynamic

all:
	make testStatic
	make testShared
	make testDynamic

clean:
	rm -f *.o *.a *.so exec $(RES)static.txt $(RES)shared.txt $(RES)dynamic.txt