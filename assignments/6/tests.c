/*
 * CS 261 Data Structures
 * Assignment 6
 */

#include "CuTest.h"
#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// --- Test Helpers ---

typedef struct HistLink HistLink;
typedef struct Histogram Histogram;

struct HistLink
{
    char* key;
    int count;
    HistLink* next;
};

struct Histogram
{
    HistLink* head;
    int size;
};

void histInit(Histogram* hist)
{
    hist->head = NULL;
    hist->size = 0;
}

void histCleanUp(Histogram* hist)
{
    HistLink* link = hist->head;
    while (link != NULL)
    {
        HistLink* next = link->next;
        free(link);
        link = next;
    }
}

void histAdd(Histogram* hist, char* key)
{
    HistLink* link = hist->head;
    while (link != NULL)
    {
        if (strcmp(key, link->key) == 0 )
        {
            link->count++;
            return;
        }
        link = link->next;
    }
    link = malloc(sizeof(HistLink));
    link->key = key;
    link->count = 1;
    link->next = hist->head;
    hist->head = link;
    hist->size++;
}

/**
 * Counts the number of times each key appears in the table.
 * @param hist
 * @param map
 */
void histFromTable(Histogram* hist, HashMap* map)
{
    histInit(hist);
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        while (link != NULL)
        {
            histAdd(hist, link->key);
            link = link->next;
        }
    }
}

/**
 * Asserts that each key is unique (count is 1 for each key).
 * @param test
 * @param hist
 */
void assertHistCounts(CuTest* test, Histogram* hist)
{
    HistLink* link = hist->head;
    while (link != NULL)
    {
        CuAssertIntEquals(test, 1, link->count);
        link = link->next;
    }
}

// --- Hash Map tests ---
/*
 * Test cases:
 * - At most one link in each bucket under threshold.
 * - At most one link in each bucket over threshold.
 * - Multiple links in some buckets under threshold.
 * - Multiple links in some buckets over threshold.
 * - Multiple links in some buckets over threshold with duplicates.
 */

/**
 * Tests all hash map functions after adding and removing all of the given keys
 * and values.
 * @param test
 * @param links The key-value pairs to be added and removed.
 * @param notKeys Some keys not in the table to test contains and get.
 * @param numLinks The number of key-value pairs to be added and removed.
 * @param numNotKeys The number of keys not in the table.
 * @param numBuckets The initial number of buckets (capacity) in the table.
 */
void testCase(CuTest* test, HashLink* links, const char** notKeys, int numLinks,
              int numNotKeys, int numBuckets)
{
    HashMap* map = hashMapNew(numBuckets);
    Histogram hist;
    
    // Add links
    for (int i = 0; i < numLinks; i++)
    {
        hashMapPut(map, links[i].key, links[i].value);
    }
    
    // Print table
    printf("\nAfter adding all key-value pairs:");
    hashMapPrint(map);
    
    // Check size
    CuAssertIntEquals(test, numLinks, hashMapSize(map));
    
    // Check capacity
    CuAssertIntEquals(test, map->capacity, hashMapCapacity(map));
    
    // Check empty buckets
    int sum = 0;
    for (int i = 0; i < map->capacity; i++)
    {
        if (map->table[i] == NULL)
        {
            sum++;
        }
    }
    CuAssertIntEquals(test, sum, hashMapEmptyBuckets(map));
    
    // Check table load
    CuAssertIntEquals(test, (float)numLinks / map->capacity, hashMapTableLoad(map));
    
    // Check contains and get on valid keys.
    for (int i = 0; i < numLinks; i++)
    {
        CuAssertIntEquals(test, 1, hashMapContainsKey(map, links[i].key));
        int* value = hashMapGet(map, links[i].key);
        CuAssertPtrNotNull(test, value);
        CuAssertIntEquals(test, links[i].value, *value);
    }
    
    // Check contains and get on invalid keys.
    for (int i = 0; i < numNotKeys; i++)
    {
        CuAssertIntEquals(test, 0, hashMapContainsKey(map, notKeys[i]));
        CuAssertPtrEquals(test, NULL, hashMapGet(map, notKeys[i]));
    }
    
    // Check that all links are present and have a unique key.
    histFromTable(&hist, map);
    CuAssertIntEquals(test, numLinks, hist.size);
    assertHistCounts(test, &hist);
    histCleanUp(&hist);
    
    // Remove keys
    for (int i = 0; i < numLinks; i++)
    {
        hashMapRemove(map, links[i].key);
    }
    
    // Print table
    printf("\nAfter removing all key-value pairs:");
    hashMapPrint(map);
    
    // Check size
    CuAssertIntEquals(test, 0, hashMapSize(map));
    
    // Check capacity
    CuAssertIntEquals(test, map->capacity, hashMapCapacity(map));
    
    // Check empty buckets
    CuAssertIntEquals(test, map->capacity, hashMapEmptyBuckets(map));
    
    // Check table load
    CuAssertIntEquals(test, 0, hashMapTableLoad(map));
    
    // Check contains and get on valid keys.
    for (int i = 0; i < numLinks; i++)
    {
        CuAssertIntEquals(test, 0, hashMapContainsKey(map, links[i].key));
        CuAssertPtrEquals(test, NULL, hashMapGet(map, links[i].key));
    }
    
    // Check contains and get on invalid keys.
    for (int i = 0; i < numNotKeys; i++)
    {
        CuAssertIntEquals(test, 0, hashMapContainsKey(map, notKeys[i]));
        CuAssertPtrEquals(test, NULL, hashMapGet(map, notKeys[i]));
    }
    
    // Check that there are no links in the table.
    histFromTable(&hist, map);
    CuAssertIntEquals(test, 0, hist.size);
    assertHistCounts(test, &hist);
    histCleanUp(&hist);
    
    hashMapDelete(map);
}

/**
 * Tests hash map functions for a table with no more than one link
 * in each bucket and without hitting the table load threshold.
 * @param test
 */
void testSingleUnder(CuTest* test)
{
    printf("\n--- Testing single-link chains under threshold ---\n");
    HashLink links[] = {
        { .key = "a", .value = 0, .next = NULL },
        { .key = "c", .value = 1, .next = NULL },
        { .key = "d", .value = 2, .next = NULL },
        { .key = "f", .value = 3, .next = NULL },
        { .key = "g", .value = 4, .next = NULL }
    };
    const char* notKeys[] = { "b", "e", "h" };
    testCase(test, links, notKeys, 5, 3, 10);
}

/**
 * Tests hash map functions for a table with no more than one link
 * in each bucket while hitting the table load threshold.
 * @param test
 */
void testSingleOver(CuTest* test)
{
    printf("\n--- Testing single-link chains over threshold ---\n");
    HashLink links[] = {
        { .key = "a", .value = 0, .next = NULL },
        { .key = "c", .value = 1, .next = NULL },
        { .key = "d", .value = 2, .next = NULL },
        { .key = "f", .value = 3, .next = NULL },
        { .key = "g", .value = 4, .next = NULL }
    };
    const char* notKeys[] = { "b", "e", "h" };
    testCase(test, links, notKeys, 5, 3, 1);
}

/**
 * Tests hash map functions for a table with 2+ links in some buckets without
 * hitting the table load threshold.
 * @param test
 */
void testMultipleUnder(CuTest* test)
{
    printf("\n--- Testing multiple-link chains under threshold ---\n");
    HashLink links[] = {
        { .key = "ab", .value = 0, .next = NULL },
        { .key = "c", .value = 1, .next = NULL },
        { .key = "ba", .value = 2, .next = NULL },
        { .key = "f", .value = 3, .next = NULL },
        { .key = "gh", .value = 4, .next = NULL }
    };
    const char* notKeys[] = { "b", "e", "hg" };
    testCase(test, links, notKeys, 5, 3, 10);
}

/**
 * Tests hash map functions for a table with 2+ links in some buckets while
 * hitting the table load threshold.
 * @param test
 */
void testMultipleOver(CuTest* test)
{
    printf("\n--- Testing multiple-link chains over threshold ---\n");
    HashLink links[] = {
        { .key = "ab", .value = 0, .next = NULL },
        { .key = "c", .value = 1, .next = NULL },
        { .key = "ba", .value = 2, .next = NULL },
        { .key = "f", .value = 3, .next = NULL },
        { .key = "gh", .value = 4, .next = NULL }
    };
    const char* notKeys[] = { "b", "e", "hg" };
    testCase(test, links, notKeys, 5, 3, 1);
}

/**
 * Tests that values are updated when inserting with a key already in the table.
 * Also tests that keys remain unique after insertion (no duplicate links).
 * @param test
 */
void testValueUpdate(CuTest* test)
{
    int numLinks = 5;
    printf("\n--- Testing value updates ---\n");
    HashLink links[] = {
        { .key = "ab", .value = 0, .next = NULL },
        { .key = "c", .value = 1, .next = NULL },
        { .key = "ba", .value = 2, .next = NULL },
        { .key = "ab", .value = 3, .next = NULL },
        { .key = "gh", .value = 4, .next = NULL }
    };
    
    HashMap* map = hashMapNew(1);
    
    // Add links
    for (int i = 0; i < numLinks; i++)
    {
        hashMapPut(map, links[i].key, links[i].value);
    }
    
    // Print table
    printf("\nAfter adding all key-value pairs:");
    hashMapPrint(map);
    
    int* value = hashMapGet(map, "ab");
    CuAssertPtrNotNull(test, value);
    CuAssertIntEquals(test, 3, *value);
    
    Histogram hist;
    histFromTable(&hist, map);
    CuAssertIntEquals(test, numLinks - 1, hist.size);
    assertHistCounts(test, &hist);
    histCleanUp(&hist);
    
    hashMapDelete(map);
}

// --- Test Suite ---

void addAllTests(CuSuite* suite)
{
    SUITE_ADD_TEST(suite, testSingleUnder);
    SUITE_ADD_TEST(suite, testSingleOver);
    SUITE_ADD_TEST(suite, testMultipleUnder);
    SUITE_ADD_TEST(suite, testMultipleOver);
    SUITE_ADD_TEST(suite, testValueUpdate);
}

int main()
{
    CuSuite* suite = CuSuiteNew();
    addAllTests(suite);
    CuSuiteRun(suite);
    CuString* output = CuStringNew();
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("\n%s\n", output->buffer);
    CuStringDelete(output);
    CuSuiteDelete(suite);
    return 0;
}

