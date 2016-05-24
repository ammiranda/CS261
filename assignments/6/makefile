CC = gcc
CFLAGS = -g -Wall -std=c99

all : tests prog

prog : main.o hashMap.o
	$(CC) $(CFLAGS) -o $@ $^

tests : tests.o hashMap.o CuTest.o
	$(CC) $(CFLAGS) -o $@ $^

spellChecker : spellChecker.o hashMap.o
	$(CC) $(CFLAGS) -o $@ $^

main.o : main.c hashMap.h

tests.o : tests.c CuTest.h hashMap.h

hashMap.o : hashMap.h hashMap.c

CuTest.o : CuTest.h CuTest.c

spellChecker.o : spellChecker.c hashMap.h

.PHONY : clean memCheckTests memCheckProg

memCheckTests :
	valgrind --tool=memcheck --leak-check=yes tests

memCheckProg :
	valgrind --tool=memcheck --leak-check=yes prog

memCheckSpellChecker :
	valgrind --tool=memcheck --leak-check=yes spellChecker

clean :
	-rm *.o
	-rm tests
	-rm prog
	-rm spellChecker
