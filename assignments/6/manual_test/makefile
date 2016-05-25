CC = gcc
CFLAGS = -g -Wall -std=c99

all: prog

prog : main.o hashMap.o
	$(CC) $(CFLAGS) -o $@ $^

main.o : main.c hashMap.h

hashMap.o : hashMap.h hashMap.c

clean :
	-rm *.o
	-rm prog