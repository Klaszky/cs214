CC = gcc

CFLAGS = -g -Wall

default: part1_main

part1_main: part1_main.o part1_functions.o
	$(CC) $(CFLAGS) -o p1 part1_main.o part1_functions.o

part1_functions.o: part1_functions.c part1_functions.h
	$(CC) $(CFLAGS) -c part1_functions.c

clean:
	$(RM) part1_main *.o