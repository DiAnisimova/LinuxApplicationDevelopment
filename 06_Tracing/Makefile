CC = gcc
CFLAGS = -Wall -g

.PHONY: all clean test

all: move overload_remove.so

move: move.c
	$(CC) $(CFLAGS) -o move move.c

overload_remove.so: overload_remove.c
	$(CC) $(CFLAGS) -fPIC -shared -o overload_remove.so overload_remove.c -ldl

test: move overload_remove.so
	chmod +x tests.sh
	./tests.sh

clean:
	rm -f move overload_remove.so
	rm -f infile.txt outfile.txt
	rm -f PROTECT_overload_remove.c
	rm -f *.o
