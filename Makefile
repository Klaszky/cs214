PROGRAMS = pointersorter

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic

%: %.c %.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: all clean

all: $(PROGRAMS)

clean:
	@rm -f *.c $(PROGRAMS)
