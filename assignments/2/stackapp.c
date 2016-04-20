/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	DynArr *stack;
	stack = newDynArr(20); 
	/* FIXME: You will write this function */
	char next = nextChar(s);
	while (next != '\0') {
                if (next == '(') {
			pushDynArr(stack, ')');
		} else if (next == '{') {
			pushDynArr(stack, '}');
		} else if (next == '[') {
			pushDynArr(stack, ']');
		} else if (next == topDynArr(stack)) {
			popDynArr(stack);	
		} else {
			deleteDynArr(stack);
			return 0;
		}
		next = nextChar(s); 
	}
	int empty = isEmptyDynArr(stack);
	deleteDynArr(stack);

	return empty;
}

int main(int argc, char* argv[]){
	
	printf("Assignment 2\n");
	
	if (argc > 1) {
		char* s=argv[1];	
		int res;
	
		res = isBalanced(s);

		if (res)
			printf("The string %s is balanced\n",s);
		else 
			printf("The string %s is not balanced\n",s);
	} else {
		printf("No string was provided\n");
	}
	return 0;	
}

