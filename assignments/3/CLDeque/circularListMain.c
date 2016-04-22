#include "circularList.h"
#include <stdio.h>

int main()
{
	struct CircularList* deque = circularListCreate();
	circularListAddBack(deque, (TYPE)1);
	circularListAddBack(deque, (TYPE)2);
	circularListAddBack(deque, (TYPE)3);
	circularListPrint(deque);
	circularListAddFront(deque, (TYPE)4);
	circularListAddFront(deque, (TYPE)5);
	circularListAddFront(deque, (TYPE)6);
	circularListPrint(deque);

  	printf("printing first and last node values\n");
	printf("%g\n", circularListFront(deque));
	printf("%g\n", circularListBack(deque));

	circularListRemoveFront(deque);
	circularListRemoveBack(deque);
	printf("after removing front and back\n");
	circularListPrint(deque);

	circularListReverse(deque);
	printf("reversed list\n");
	circularListPrint(deque);

	circularListDestroy(deque);

	return 0;
}
