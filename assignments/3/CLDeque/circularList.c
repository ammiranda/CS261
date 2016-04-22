#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this
	struct Link *link;
	link = (struct Link *) malloc( sizeof(struct Link) );
	link->next = link;
	link->prev = link;
	list->size = 0;
	list->sentinel = link;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this
	struct Link *link;
	link = (struct Link *) malloc( sizeof(struct Link) );
	link->next = NULL;
	link->prev = NULL;
	link->value = value;
	return link;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
	struct Link *newLink;
	newLink = createLink(value);
	newLink->prev = link;
	newLink->next = link->next;
	link->next->prev = newLink;
	link->next = newLink;
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this
	struct Link *iterator;
	iterator = list->sentinel;
	while (iterator->next != link) {
		iterator = iterator->next;
	}
	iterator->next = link->next;
	free(link);
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// FIXME: you must write this
	while(!circularListIsEmpty(list)) {
	   circularListRemoveFront(list);
	}
	free(list->sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this
	TYPE ans = 0;
	if (list->sentinel != NULL) {
		ans = list->sentinel->next->value;
	}
	return ans;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this
	TYPE ans = 0;
	if (list->sentinel != NULL) {
		ans = list->sentinel->prev->value;
	}
	return ans;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this
	if (list->size > 0) {
		removeLink(list, list->sentinel->next);
	}
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this
	if (list->size > 0) {
		removeLink(list, list->sentinel->prev);
	}
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
	return list->size == 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this
	struct Link *iterator = list->sentinel->next;
	int i = 0;
	while (i < list->size) {
		printf("%g\n", iterator->value);
		iterator = iterator->next;
		i++;
	}
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// FIXME: you must write this
	struct Link *prev = NULL;
	struct Link *current = list->sentinel->next;
	struct Link *next;
	int i = 0;
	while (i < list->size) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
		i++;
	}
	list->sentinel->next = prev;
}
