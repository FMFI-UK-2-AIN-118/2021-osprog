program: number.o program.o libnumber.so
	gcc -o program program.o -lnumber -L.

program.o: number.h program.c
	gcc -c -o program.o program.c
	
number.o: number.c number.h
	gcc -c -o number.o -fPIC number.c

libnumber.so: number.o
	gcc -o libnumber.so -shared number.o

clean:
	-rm -f number.o program.o

distclean: clean
	-rm -f program libnumber.so

test: 
	@export LD_LIBRARY_PATH=$$PWD; ./program; echo $$?



