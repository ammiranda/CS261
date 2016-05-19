/*
 * CS 261 Data Structures
 * Assignment 5 unit tests
 * Author: Sean Moore
 * Date: 4/29/2016
 */

#include "CuTest.h"
#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// --- Internal functions to be tested ---

void adjustHeap(DynamicArray* heap, int last, int position, compareFunction compare);
void buildHeap(DynamicArray* heap, compareFunction compare);

// --- Test helper functions ---

void shuffle(DynamicArray* array)
{
    for (int i = 0; i < dySize(array); i++)
    {
        int j = rand() % dySize(array);
        dySwap(array, i, j);
    }
}

Task* createTasks(const int n)
{
    Task* tasks = malloc(sizeof(Task) * n);
    for (int i = 0; i < n; i++)
    {
        tasks[i].priority = i;
        sprintf(tasks[i].name, "Task %d", i);
    }
    return tasks;
}

void assertHeapProperty(CuTest* test, DynamicArray* heap)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        int priority = ((Task*)dyGet(heap, i))->priority;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < dySize(heap))
        {
            int leftPriority = ((Task*)dyGet(heap, left))->priority;
            CuAssertTrue(test, priority <= leftPriority);
        }
        if (right < dySize(heap))
        {
            int rightPriority = ((Task*)dyGet(heap, right))->priority;
            CuAssertTrue(test, priority <= rightPriority);
        }
    }
}

// --- Tests ----

/*
 * adjustHeap
 * buildHeap
 * dyHeapAdd
 * dyHeapRemoveMin
 * dyHeapGetMin
 * dyHeapSort
 * taskNew
 * taskCompare
 */

void testAdjustHeap(CuTest* test)
{
    const int n = 100;
    Task* tasks = createTasks(n);
    for (int j = 0; j < n; j++)
    {
        DynamicArray* heap = dyNew(1);
        for (int i = 0; i < n; i++)
        {
            dyAdd(heap, &tasks[i]);
        }
        for (int i = 0; i < n; i++)
        {
            dyPut(heap, &tasks[rand() % n], 0);
            adjustHeap(heap, dySize(heap) - 1, 0, taskCompare);
            assertHeapProperty(test, heap);
        }
        dyDelete(heap);
    }
    free(tasks);
}

void testBuildHeap(CuTest* test)
{
    const int n = 100;
    Task* tasks = createTasks(n);
    DynamicArray* heap = dyNew(1);
    for (int i = 0; i < n; i++)
    {
        dyAdd(heap, &tasks[i]);
    }
    for (int i = 0; i < n; i++)
    {
        shuffle(heap);
        buildHeap(heap, taskCompare);
        CuAssertIntEquals(test, n, dySize(heap));
        assertHeapProperty(test, heap);
    }
    dyDelete(heap);
    free(tasks);
}

void testDyHeapAdd(CuTest* test)
{
    const int n = 100;
    Task* tasks = createTasks(n);
    for (int i = 0; i < n; i++)
    {
        DynamicArray* heap = dyNew(1);
        for (int j = 0; j < n; j++)
        {
            dyHeapAdd(heap, &tasks[rand() % n], taskCompare);
            CuAssertIntEquals(test, j + 1, dySize(heap));
            assertHeapProperty(test, heap);
        }
        dyDelete(heap);
    }
    free(tasks);
}

void testDyHeapRemoveMin(CuTest* test)
{
    const int n = 100;
    Task* tasks = createTasks(n);
    DynamicArray* heap = dyNew(1);
    for (int i = 0; i < n; i++)
    {
        dyAdd(heap, &tasks[i]);
    }
    for (int i = 0; i < n; i++)
    {
        CuAssertIntEquals(test, n - i, dySize(heap));
        CuAssertTrue(test, dyGet(heap, 0) == &tasks[i]);
        dyHeapRemoveMin(heap, taskCompare);
        assertHeapProperty(test, heap);
        CuAssertIntEquals(test, n - i - 1, dySize(heap));
    }
    dyDelete(heap);
    free(tasks);
}

void testDyHeapGetMin(CuTest* test)
{
    const int n = 10;
    DynamicArray* heap = dyNew(1);
    Task* tasks = createTasks(n);
    for (int i = 0; i < n; i++)
    {
        dyAdd(heap, &tasks[i]);
    }
    CuAssertPtrNotNull(test, dyHeapGetMin(heap));
    CuAssertTrue(test, dyGet(heap, 0) == dyHeapGetMin(heap));
    shuffle(heap);
    CuAssertPtrNotNull(test, dyHeapGetMin(heap));
    CuAssertTrue(test, dyGet(heap, 0) == dyHeapGetMin(heap));
    free(tasks);
    dyDelete(heap);
}

void testDyHeapSort(CuTest* test)
{
    const int n = 100;
    struct Task* tasks = createTasks(n);
    DynamicArray* heap = dyNew(1);
    for (int i = 0; i < n; i++)
    {
        dyAdd(heap, &tasks[i]);
    }
    shuffle(heap);
    dyHeapSort(heap, taskCompare);
    CuAssertIntEquals(test, n, dySize(heap));
    for (int i = 0; i < n; i++)
    {
        CuAssertTrue(test, dyGet(heap, i) == &tasks[n - i - 1]);
    }
    free(tasks);
    dyDelete(heap);
}

void testTaskNew(CuTest* test)
{
    const int n = 4;
    char* names[] = {
        "get up",
        "eat food",
        "study",
        "go to bed"
    };
    for (int i = 0; i < n; i++)
    {
        Task* task = taskNew(i, names[i]);
        CuAssertPtrNotNull(test, task);
        CuAssertStrEquals(test, names[i], task->name);
        CuAssertIntEquals(test, i, task->priority);
        taskDelete(task);
    }
}

void testTaskCompare(CuTest* test)
{
    const int n = 10;
    Task tasks[n];
    for (int i = 0; i < n; i++)
    {
        tasks[i].priority = i;
        sprintf(tasks[i].name, "Task %d", i);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int relation = taskCompare(&tasks[i], &tasks[j]);
            if (i < j)
            {
                CuAssertTrue(test, relation < 0);
            }
            else if (i > j)
            {
                CuAssertTrue(test, relation > 0);
            }
            else
            {
                CuAssertIntEquals(test, 0, relation);
            }
        }
    }
}

/**
 * You may uncomment the corresponding line in addTests() to run this test
 * if it is useful to you.
 * @param test
 */
void testExtraCredit(CuTest* test)
{
    const int n = 10;
    Task* tasks = createTasks(n);
    DynamicArray* heap = dyNew(1);
    int same = rand() % n;
    for (int i = 0; i < n; i++)
    {
        tasks[i].priority = same;
        dyHeapAdd(heap, &tasks[i], taskCompare);
    }
    for (int i = 0; i < n; i++)
    {
        CuAssertTrue(test, dyHeapGetMin(heap) == &tasks[i]);
        dyHeapRemoveMin(heap, taskCompare);
    }
    dyDelete(heap);
    free(tasks);
}

/**
 * Just a skeleton code function test.
 * @param test
 */
void testDyOrderedAdd(CuTest* test)
{
    const int n = 100;
    Task* tasks = createTasks(n);
    DynamicArray* array = dyNew(1);
    for (int i = 0; i < n; i++)
    {
        dyOrderedAdd(array, &tasks[rand() % n], taskCompare);
    }
    int maxPriority = ((Task*)dyGet(array, 0))->priority;
    for (int i = 0; i < n; i++)
    {
        Task* task = (Task*)dyGet(array, i);
        CuAssertTrue(test, task->priority >= maxPriority);
        if (task->priority > maxPriority)
        {
            maxPriority = task->priority;
        }
    }
    dyDelete(array);
    free(tasks);
}

// --- Test suite ---

/*
 * To add a test, just write a function above with the following prototype,
 * void testFunction(CuTest* test)
 * , and add it to this function with the following line of code,
 * SUITE_ADD_TEST(suite, testFunction);
 *
 * See CuTest.h for all the different assert macro functions.
 */
void addTests(CuSuite* suite)
{
    SUITE_ADD_TEST(suite, testAdjustHeap);
    SUITE_ADD_TEST(suite, testBuildHeap);
    SUITE_ADD_TEST(suite, testDyHeapAdd);
    SUITE_ADD_TEST(suite, testDyHeapRemoveMin);
    SUITE_ADD_TEST(suite, testDyHeapGetMin);
    SUITE_ADD_TEST(suite, testDyHeapSort);
    SUITE_ADD_TEST(suite, testTaskNew);
    SUITE_ADD_TEST(suite, testTaskCompare);
    //SUITE_ADD_TEST(suite, testExtraCredit);
    //SUITE_ADD_TEST(suite, testDyOrderedAdd);
}

void runTests()
{
    srand(0);
    CuSuite* suite = CuSuiteNew();
    CuString* output = CuStringNew();
    addTests(suite);
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    CuSuiteDelete(suite);
    CuStringDelete(output);
}

int main()
{
    runTests();
    return 0;
}
