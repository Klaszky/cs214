CC = gcc

CFLAGS = -g -Wall

default: test

test: test.o mymalloc.o
	$(CC) $(CFLAGS) -o test test.o mymalloc.o

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c

clean:
	$(RM) test *.o
