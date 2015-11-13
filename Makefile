CC = gcc
JC = javac

IDIR = include
SDIR = src
BDIR = bin

# -g flag: adds debugging information to executable file
# -Wall flag: turns on most compiler warnings
CFLAGS = -g -Wall -O3 -lm

INCLUDES = -I./$(IDIR)

all: bin/main bin/DataGenerator.class

bin/main: main.o
	$(CC) main.o -o bin/main

main.o: ditem.o
	$(CC) ditem.o src/main.c -c $(INCLUDES)

ditem.o: src/ditem.c
	$(CC) src/ditem.c $(CFLAGS) $(INCLUDES) -c

bin/DataGenerator.class: src/java/DataGenerator.java
	$(JC) src/java/DataGenerator.java -d bin/



clean:
	$(RM) -f *.o *~ $(IDIR)/*~ $(SDIR)/*~ bin/*.class bin/*.txt
run:
	./bin/main
