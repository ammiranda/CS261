/*
 * CS 261 Assignment 5
 * Name: Alexander Miranda
 * Date: May 20, 2016
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(dySize(heap));
    dyCopy(heap, temp);
    while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    printf("\n");
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    char *filename = malloc(sizeof(char) * 256);
    char *desc = malloc(sizeof(char) * 256);
    int priority;
    // FIXME: Implement
    switch(command) {
        case 'l':
            printf("Please enter the filename: ");
            fgets(filename, 100, stdin);
            if (filename[strlen(filename) - 1] == '\n') {
                filename[strlen(filename) - 1] = 0;
            }
            FILE *reader = fopen(filename, "r");
            listLoad(list, reader);
            printf("The list has been loaded successfully from the file.\n");
            fclose(reader);
            break;

        case 's':
            printf("Please enter the filename: ");
            fgets(filename, 100, stdin);
            if (filename[strlen(filename) - 1] == '\n') {
                filename[strlen(filename) - 1] = 0;
            }
            FILE *writer = fopen(filename, "w+");
            listSave(list, writer);
            printf("The list was saved to the specified file.\n");
            fclose(writer);
            break;

        case 'a':
            printf("Please enter the task description: ");
            fgets(desc, 100, stdin);
            if (desc[strlen(desc) - 1] == '\n') {
                desc[strlen(desc) - 1] = 0;
            }
            printf("Please enter the task priority (0-999): ");
            scanf("%d", &priority);
            while (getchar() != '\n');
            Task *task = taskNew(priority, desc);
            dyHeapAdd(list, task, taskCompare);
            printf("The task '%s' has been added to the list.\n", desc);
            break;

        case 'g':
            if (dySize(list) != 0) {
                printf("Your first task is: %s\n", ((struct Task *)dyHeapGetMin(list))->name);
            } else {
                printf("Your to-do list is empty!\n");
            }
            break;

        case 'r':
            if (dySize(list) == 0) {
                printf("Your to-do list is empty!\n");
            } else {
                desc = ((struct Task *)dyHeapGetMin(list))->name;
                dyHeapRemoveMin(list, taskCompare);
                printf("Your first task '%s' has been removed from the list.\n", desc);
            }
            break;

        case 'p':
            if (dySize(list) == 0) {
                printf("Your to-do list is empty!\n");
            } else {
                listPrint(list);
            }
            break;

        case 'e':
            printf("Bye!\n");
            break;
    }
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
    dyDelete(list);
    return 0;
}
