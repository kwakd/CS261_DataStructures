CC=gcc --std=c99 -g

all: test unittest

unittest: unittest.c pq.o dynarray.o
	$(CC) unittest.c pq.o dynarray.o -o unittest

test: test.c pq.o dynarray.o
	$(CC) test.c pq.o dynarray.o -o test

dynarray.o: dynarray.c dynarray.h
	$(CC) -c dynarray.c

pq.o: pq.c pq.h
	$(CC) -c pq.c

clean:
	rm -f *.o test unittest
	rm -rf *.dSYM/
