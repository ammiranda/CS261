#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	// FIXME: you must write this
	struct Link *start;
	struct Link *end;
	start = (struct Link *) malloc( sizeof(struct Link) );
	end = (struct Link *) malloc( sizeof(struct Link) );
	start->next = end;
	end->prev = start;
	list->frontSentinel = start;
	list->backSentinel = end;
	list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(link != NULL);
	struct Link *newLink;
	newLink = (struct Link *) malloc( sizeof(struct Link) );
	newLink->value = value;
	newLink->prev = link->prev;
	newLink->next = link;
	link->prev->next = newLink;
	link->prev = newLink;
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(link != NULL);
	link->prev->next = link->next;
	link->next->prev = link->prev;
	free(link);
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != NULL);
	addLinkBefore(list, list->frontSentinel->next, value);	
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != NULL);
	addLinkBefore(list, list->backSentinel, value);	
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(!linkedListIsEmpty(list));
	return (list->frontSentinel->next->value);
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(!linkedListIsEmpty(list));
	return (list->backSentinel->prev->value);
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
	return (list->size == 0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(!linkedListIsEmpty(list));
	struct Link *cur = list->frontSentinel->next;
	assert(cur != 0);
	while(cur != list->backSentinel) {
		printf("%d\n", cur->value);
		cur = cur->next;
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	linkedListAddFront(list, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(!linkedListIsEmpty(list));
	struct Link *cur = list->frontSentinel->next;
	while(cur != list->backSentinel->prev) {
		if (cur->value == value) {
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(!linkedListIsEmpty(list));
	struct Link *cur = list->frontSentinel->next;
	while (cur != list->backSentinel) {
		if (cur->value == value) {
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			free(cur);
			list->size--;
			break;
		}
		cur = cur->next;
	}
}
