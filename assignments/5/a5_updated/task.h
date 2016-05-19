#ifndef TASK_H
#define TASK_H

#define TASK_NAME_SIZE 128

typedef struct Task Task;

struct Task
{
    int priority;
    char name[TASK_NAME_SIZE];
};

Task* taskNew(int priority, char* name);
void taskDelete(Task* task);
int taskCompare(void* left, void* right);
void taskPrint(void* value);

#endif /* TASK_H */

