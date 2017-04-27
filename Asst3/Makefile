CC = gcc

CFLAGS = -Wall -Wextra -g

default: netclient netfileserver

netclient: netclient.o libnetfiles.o
	$(CC) $(CLFAGS) -o netclient netclient.o libnetfiles.o

netfileserver: netfileserver.o libnetfiles.o
	$(CC) $(CLFAGS) -o netfileserver netfileserver.o libnetfiles.o 

libnetfiles: libnetfiles.c libnetfiles.h
	$(CC) $(CLFAGS) -c libnetfiles.c

clean:
	$(RM) netfileserver netclient *.o