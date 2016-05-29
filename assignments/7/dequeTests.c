/*
 * CS 261 Data Structures
 * Assignment 7
 * Author: Sean Moore
 * Date: 5/19/2016
 */

#include "cutest/CuTest.h"
#include "deque.h"
#include <stdlib.h>

int** createValues(int n)
{
    int** values = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; ++i)
    {
        values[i] = malloc(sizeof(int));
        *values[i] = i;
    }
    return values;
}

void freeValues(int** values, int n)
{
    for (int i = 0; i < n; ++i)
    {
        free(values[i]);
    }
    free(values);
}

void testPushFrontPopFront(CuTest* test)
{
    const int N = 100;
    int** values = createValues(N);
    Deque* deque = dequeNew();
    CuAssertIntEquals(test, 1, dequeIsEmpty(deque));
    for (int i = 0; i < N; ++i)
    {
        dequePushFront(deque, values[i]);
    }
    for (int i = 0; i < N; ++i)
    {
        CuAssertIntEquals(test, 0, dequeIsEmpty(deque));
        CuAssertPtrEquals(test, values[N - i - 1], dequeFront(deque));
        CuAssertPtrEquals(test, values[0], dequeBack(deque));
        dequePopFront(deque);
    }
    CuAssertIntEquals(test, 1, dequeIsEmpty(deque));
    dequeDelete(deque);
    freeValues(values, N);
}

void testPushFrontPopBack(CuTest* test)
{
    const int N = 100;
    int** values = createValues(N);
    Deque* deque = dequeNew();
    CuAssertIntEquals(test, 1, dequeIsEmpty(deque));
    for (int i = 0; i < N; ++i)
    {
        dequePushFront(deque, values[i]);
    }
    for (int i = 0; i < N; ++i)
    {
        CuAssertIntEquals(test, 0, dequeIsEmpty(deque));
        CuAssertPtrEquals(test, values[N - 1], dequeFront(deque));
        CuAssertPtrEquals(test, values[i], dequeBack(deque));
        dequePopBack(deque);
    }
    CuAssertIntEquals(test, 1, dequeIsEmpty(deque));
    dequeDelete(deque);
    freeValues(values, N);
}

void testPushBackPopFront(CuTest* test)
{
    const int N = 100;
    int** values = createValues(N);
    Deque* deque = dequeNew();
    CuAssertIntEquals(test, 1, dequeIsEmpty(deque));
    for (int i = 0; i < N; ++i)
    {
        dequePushBack(deque, values[i]);
    }
    for (int i = 0; i < N; ++i)
    {
        CuAssertIntEquals(test, 0, dequeIsEmpty(deque));
        CuAssertPtrEquals(test, values[N - 1], dequeBack(deque));
        CuAssertPtrEquals(test, values[i], dequeFront(deque));
        dequePopFront(deque);
    }
    CuAssertIntEquals(test, 1, dequeIsEmpty(deque));
    dequeDelete(deque);
    freeValues(values, N);
}

void testPushBackPopBack(CuTest* test)
{
    const int N = 100;
    int** values = createValues(N);
    Deque* deque = dequeNew();
    CuAssertIntEquals(test, 1, dequeIsEmpty(deque));
    for (int i = 0; i < N; ++i)
    {
        dequePushBack(deque, values[i]);
    }
    for (int i = 0; i < N; ++i)
    {
        CuAssertIntEquals(test, 0, dequeIsEmpty(deque));
        CuAssertPtrEquals(test, values[N - i - 1], dequeBack(deque));
        CuAssertPtrEquals(test, values[0], dequeFront(deque));
        dequePopBack(deque);
    }
    CuAssertIntEquals(test, 1, dequeIsEmpty(deque));
    dequeDelete(deque);
    freeValues(values, N);
}

CuSuite* getDequeTestSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testPushFrontPopFront);
    SUITE_ADD_TEST(suite, testPushFrontPopBack);
    SUITE_ADD_TEST(suite, testPushBackPopFront);
    SUITE_ADD_TEST(suite, testPushBackPopBack);
    return suite;
}