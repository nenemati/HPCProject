CC = gcc
JC = javac

# -g flag: adds debugging information to executable file
# -Wall flag: turns on most compiler warnings
CFLAGS = -g -Wall -O3 -lm -fopenmp
JFLAGS = -d bin/

all: bin/main bin/DataGenerator.class bin/dgen

bin/main: main.c
	$(CC) main.c $(CFLAGS) -o bin/main

bin/DataGenerator.class: DataGenerator.java
	$(JC) DataGenerator.java $(JFLAGS)

bin/dgen: dgen.c
	$(CC) dgen.c -o bin/dgen

clean:
	$(RM) *.o *~ bin/*
