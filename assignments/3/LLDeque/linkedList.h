#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#ifndef TYPE
#define TYPE int
#endif

#ifndef LT
#define LT(A, B) ((A) < (B))
#endif

#ifndef EQ
#define EQ(A, B) ((A) == (B))
#endif

struct LinkedList;

struct LinkedList* linkedListCreate();
void linkedListDestroy(struct LinkedList* list);
void linkedListPrint(struct LinkedList* list);

// Deque interface

int linkedListIsEmpty(struct LinkedList* list);
void linkedListAddFront(struct LinkedList* list, TYPE value);
void linkedListAddBack(struct LinkedList* list, TYPE value);
TYPE linkedListFront(struct LinkedList* list);
TYPE linkedListBack(struct LinkedList* list);
void linkedListRemoveFront(struct LinkedList* list);
void linkedListRemoveBack(struct LinkedList* list);

// Bag interface

void linkedListAdd(struct LinkedList* list, TYPE value);
int linkedListContains(struct LinkedList* list, TYPE value);
void linkedListRemove(struct LinkedList* list, TYPE value);

#endif