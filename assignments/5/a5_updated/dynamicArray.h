#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

/*
 * CS 261 Data Structures
 * Name: Sean Moore
 * Date: April 27, 2016
 */

#define TYPE void*

typedef struct DynamicArray DynamicArray;
typedef int (*compareFunction)(TYPE, TYPE);
typedef void (*printFunction)(TYPE);

struct DynamicArray;

DynamicArray* dyNew(int capacity);
void dyDelete(DynamicArray* array);

// Dynamic array
void dyAdd(DynamicArray* array, TYPE value);
void dyAddAt(DynamicArray* array, TYPE value, int position);
void dyPut(DynamicArray* array, TYPE value, int position);
void dyRemoveAt(DynamicArray* array, int position);
TYPE dyGet(DynamicArray* array, int position);
int dySize(DynamicArray* array);
void dySwap(DynamicArray* array, int position1, int position2);

// Stack
void dyStackPush(DynamicArray* stack, TYPE value);
void dyStackPop(DynamicArray* stack);
TYPE dyStackTop(DynamicArray* stack);
int dyStackIsEmpty(DynamicArray* stack);

// Bag
void dyBagAdd(DynamicArray* bag, TYPE value);
void dyBagRemove(DynamicArray* bag, TYPE value, compareFunction compare);
int dyBagContains(DynamicArray* bag, TYPE value, compareFunction compare);

// Ordered bag
void dyOrderedAdd(DynamicArray* bag, TYPE value, compareFunction compare);
void dyOrderedRemove(DynamicArray* bag, TYPE value, compareFunction compare);
int dyOrderedContains(DynamicArray* bag, TYPE value, compareFunction compare);

// Heap
void dyHeapAdd(DynamicArray* heap, TYPE value, compareFunction compare);
void dyHeapRemoveMin(DynamicArray* heap, compareFunction compare);
TYPE dyHeapGetMin(DynamicArray* heap);
void dyHeapSort(DynamicArray* heap, compareFunction compare);

// Iterator
typedef struct DynamicArrayIterator DynamicArrayIterator;

struct DynamicArrayIterator
{
    DynamicArray* array;
    int current;
};

DynamicArrayIterator* dyIteratorNew(DynamicArray* array);
void dyIteratorDelete(DynamicArrayIterator* iterator);
int dyIteratorHasNext(DynamicArrayIterator* iterator);
TYPE dyIteratorNext(DynamicArrayIterator* iterator);
void dyIteratorRemove(DynamicArrayIterator* iterator);

// Utility
/**
 * Prints the size, capacity, and elements of array, calling the print
 * function on each element.
 * @param array
 * @param print
 */
void dyPrint(DynamicArray* array, printFunction print);
void dyCopy(DynamicArray* source, DynamicArray* destination);

#endif