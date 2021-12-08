CC=gcc --std=c99 -g

all: test

test: test.c students.o dynarray.o
	$(CC) test.c students.o dynarray.o -o test

dynarray.o: dynarray.c dynarray.h
	$(CC) -c dynarray.c

students.o: students.c students.h
	$(CC) -c students.c

clean:
	rm -f test students.o dynarray.o
