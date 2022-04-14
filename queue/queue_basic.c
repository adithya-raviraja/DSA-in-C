#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int g_isFirstEntry = true;

typedef struct queue_basic_s
{
    int front;
    int rear;
    int capacity;
    int *valArr;
} queue_basic_t;

void getFrontandRear(queue_basic_t *queue)
{
    printf("REAR: %d, FRONT: %d\n", queue->valArr[queue->rear], queue->valArr[queue->front]);
    return;
}

queue_basic_t *allocQueue(int size)
{
    queue_basic_t *queue = NULL;
    queue = (queue_basic_t *)malloc(sizeof(queue_basic_t));
    queue->capacity = size;
    int *arr = (int *)malloc(queue->capacity * sizeof(int));
    queue->valArr = arr;
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

void reallocQueue(queue_basic_t *queue, int newSize)
{
    queue->valArr = (int *)realloc(queue->valArr, newSize * sizeof(int));
    queue->capacity = newSize;
    return;
}

void enqueue(queue_basic_t *queue, int element)
{
    if (queue->capacity - 1 == queue->front)
    {
        printf("QUEUE HAS REACH ITS MAX SIZE\n");
        printf("ALLOCATING MORE MEM\n");
        reallocQueue(queue, queue->capacity * 2);
    }
    if (g_isFirstEntry)
    {
        queue->rear++;
        g_isFirstEntry = false;
    }
    queue->front++;
    queue->valArr[queue->front] = element;
    return;
}

void dequeue(queue_basic_t *queue)
{
    if (queue->rear == queue->front)
    {
        printf("Removing last element");
        queue->front = -1;
        queue->rear = -1;
        return;
    }
    else
    {
        queue->rear++;
        return;
    }
}

int main()
{
    queue_basic_t *queue = NULL;
    int i = 0;
    queue = allocQueue(10);
    for (i = 0; i < 10; i++)
    {
        enqueue(queue, i);
        getFrontandRear(queue);
    }
    printf("###################################################\n");
    for (i = 0; i < 10; i++)
    {
        getFrontandRear(queue);
        dequeue(queue);
    }
    return 0;
}