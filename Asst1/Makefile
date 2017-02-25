CC = gcc

CFLAGS = -g -Wall

default: test memgrind memgrindv2

memgrindv2: memgrindv2.o mymalloc.o
	$(CC) $(CFLAGS) -o memgrindv2 memgrindv2.o mymalloc.o

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) -o memgrind memgrind.o mymalloc.o

test: test.o mymalloc.o
	$(CC) $(CFLAGS) -o test test.o mymalloc.o

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c

clean:
	$(RM) test memgrind *.o
