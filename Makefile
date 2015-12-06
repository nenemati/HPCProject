CC = gcc

# -g flag: adds debugging information to executable file
# -Wall flag: turns on most compiler warnings
CFLAGS = -g -Wall -O3 -lm -fopenmp -L.

all: bin/main bin/dgen

bin/main: main.c
	$(CC) main.c my_timer.c $(CFLAGS) -o bin/main

bin/dgen: dgen.c
	$(CC) dgen.c $(CLFAGS) -o bin/dgen

clean:
	$(RM) *.o *~ bin/*
