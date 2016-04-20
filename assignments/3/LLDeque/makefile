CC=gcc
CFLAGS=-Wall -std=c99

all: prog

prog: linkedList.o linkedListMain.o
	$(CC) $^ -o $@

clean:
	-rm *.o

cleanall: clean
	-rm prog