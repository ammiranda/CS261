CC=gcc
CFLAGS=-g -Wall -std=c99

all: prog

prog: circularList.o circularListMain.o
	$(CC) $^ -o $@

clean:
	-rm *.o

cleanall: clean
	-rm prog