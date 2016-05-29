CFLAGS = -g -Wall -std=c99
VPATH = cutest

all : tests prog

tests : tests.c CuTest.c dequeTests.c graphTests.c graph.o deque.o
	gcc $(CFLAGS) -o $@ $^

prog : main.c graph.o deque.o
	gcc $(CFLAGS) -o $@ $^

graph.o : graph.c
	gcc $(CFLAGS) -c -o $@ $<

deque.o : deque.c
	gcc $(CFLAGS) -c -o $@ $<

memcheckTests : tests
	valgrind --tool=memcheck --leak-check=yes tests

memcheckProg : prog
	valgrind --tool=memcheck --leak-check=yes prog

clean :
	-rm *.o
	-rm tests
	-rm prog
