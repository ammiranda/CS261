CC=gcc
CFLAGS=-Wall -std=c99

all: prog

prog: dynamicArray.o dynamicArrayMain.o
	$(CC) $^ -o $@

clean:
	-rm *.o

cleanall: clean
	-rm prog