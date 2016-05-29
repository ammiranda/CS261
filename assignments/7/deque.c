/*
 * CS 261 Data Structures
 * Assignment 7
 * Author: Sean Moore
 * Date: 5/18/2016
 */

#include "deque.h"
#include <stdlib.h>
#include <assert.h>

/**
 * Frees the given link and connects its previous and next links.
 * @param link
 */
static void removeLink(Link* link)
{
    link->prev->next = link->next;
    link->next->prev = link->prev;
    free(link);
}

/**
 * Creates a new link with the given value and inserts it after the given link.
 * @param link
 * @param value
 */
static void addLinkAfter(Link* link, Type value)
{
    Link* newLink = malloc(sizeof(Link));
    newLink->value = value;
    newLink->next = link->next;
    newLink->prev = link;
    newLink->next->prev = newLink;
    newLink->prev->next = newLink;
}

/**
 * Allocates a new deque, initializes it, and returns it.
 * @return new initialized deque.
 */
Deque* dequeNew()
{
    Deque* deque = malloc(sizeof(Deque));
    assert(deque != NULL);
    Link* sentinel = malloc(sizeof(Link));
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    deque->sentinel = sentinel;
    deque->size = 0;
    return deque;
}

/**
 * Frees allocated memory in the given deque and the deque itself.
 * @param deque
 */
void dequeDelete(Deque* deque)
{
    dequeClear(deque);
    free(deque->sentinel);
    free(deque);
}

/**
 * Creates a new link with the given value and inserts it at the front of the
 * deque. Also increments the size of the deque.
 * @param deque
 * @param value
 */
void dequePushFront(Deque* deque, Type value)
{
    addLinkAfter(deque->sentinel, value);
    ++(deque->size);
}

/**
 * Creates a new link with the given value and inserts it at the back of the
 * deque. Also increments the size of the deque.
 * @param deque
 * @param value
 */
void dequePushBack(Deque* deque, Type value)
{
    addLinkAfter(deque->sentinel->prev, value);
    ++(deque->size);
}

/**
 * Returns the value of the link at the front of the deque.
 * @param deque
 * @return value of front link.
 */
Type dequeFront(Deque* deque)
{
    assert(deque->size > 0);
    return deque->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 * @param deque
 * @return value of back link.
 */
Type dequeBack(Deque* deque)
{
    assert(deque->size > 0);
    return deque->sentinel->prev->value;
}

/**
 * Removes and frees the link at the front of the deque. Also decrements the
 * size of the deque.
 * @param deque
 */
void dequePopFront(Deque* deque)
{
    assert(deque->size > 0);
    removeLink(deque->sentinel->next);
    --(deque->size);
}

/**
 * Removes and frees the link at the back of the deque. Also decrements the
 * size of the deque.
 * @param deque
 */
void dequePopBack(Deque* deque)
{
    assert(deque->size > 0);
    removeLink(deque->sentinel->prev);
    --(deque->size);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 * @param deque
 * @return 1 if empty, 0 otherwise.
 */
int dequeIsEmpty(Deque* deque)
{
    return deque->size == 0;
}

/**
 * Removes and frees all links in the deque, except the sentinel.
 * @param deque
 */
void dequeClear(Deque* deque)
{
    while (!dequeIsEmpty(deque))
    {
        dequePopFront(deque);
    }
}