#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool g_isFirstEntry = true;

typedef struct list_s
{
    int value;
    struct list_s *next;
} list_t;

typedef struct queue_list_s
{
    int count;
    list_t *front;
    list_t *rear;
} queue_list_t;

void getFrontAndRear(queue_list_t *queue)
{
    if (queue->front != NULL && queue->rear != NULL)
    {
        printf("REAR: %d, FRONT: %d\n", queue->rear->value, queue->front->value);
    }
    else
    {
        printf("No elements inserted yet\n");
    }
    return;
}

queue_list_t *allocQueue()
{
    queue_list_t *queue = NULL;
    queue = (queue_list_t *)malloc(sizeof(queue_list_t));
    queue->count = 0;
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(queue_list_t *queue, int element)
{
    list_t *entry = NULL;
    list_t *curFront = NULL;

    entry = (list_t *)malloc(sizeof(list_t));
    entry->value = element;
    if (g_isFirstEntry)
    {
        entry->next = NULL;
        queue->front = entry;
        queue->rear = entry;
        g_isFirstEntry = false;
    }
    else
    {
        entry->next = NULL;
        curFront = queue->front;
        curFront->next = entry;
        queue->front = entry;
    }
    queue->count++;
    return;
}

void dequeue(queue_list_t *queue)
{
    list_t *curRear = NULL;
    list_t *newRear = NULL;

    if (queue->count == 0)
    {
        printf("No elements to dequeue\n");
        return;
    }
    else if (queue->count == 1)
    {
        queue->count = 0;
        free(queue->rear);
        queue->front = NULL;
        queue->rear = NULL;
    }
    else
    {
        curRear = queue->rear;
        newRear = curRear->next;
        queue->rear = newRear;
        free(curRear);
        queue->count--;
    }
}

int main()
{
    queue_list_t *queue = NULL;
    int i = 0;

    queue = allocQueue();
    for (i = 0; i < 10; i++)
    {
        enqueue(queue, i);
        getFrontAndRear(queue);
    }
    printf("############################dequeue####################\n");
    for (i = 0; i < 10; i++)
    {
        getFrontAndRear(queue);
        dequeue(queue);
    }
    dequeue(queue);
    return 0;
}