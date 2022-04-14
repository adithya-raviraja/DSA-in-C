#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int g_firstEntry = true;

typedef struct list_s
{
    int value;
    struct list_s *next;
} list_t;

typedef struct stack_list_s
{
    int capacity;
    list_t *top;
} stack_list_t;

stack_list_t *allocStack()
{
    stack_list_t *stack = NULL;
    stack = (stack_list_t *)malloc(sizeof(stack_list_t));
    stack->capacity = -1;
    return stack;
}

void push(stack_list_t *stack, int element)
{
    list_t *entry = NULL;
    entry = (list_t *)malloc(sizeof(list_t));
    entry->value = element;
    if (g_firstEntry)
    {
        entry->next = NULL;
        stack->top = entry;
        stack->capacity = 0;
        g_firstEntry = false;
    }
    else
    {
        entry->next = stack->top;
        stack->top = entry;
        stack->capacity++;
    }
}

void pop(stack_list_t *stack)
{
    list_t *headEntry = stack->top;
    if (stack->capacity == 0)
    {
        stack->top = NULL;
        free(headEntry);
        return;
    }
    if (stack->capacity == -1)
    {
        printf("No entries to pop");
        return;
    }
    if (stack->capacity > 0)
    {
        stack->top = headEntry->next;
        free(headEntry);
        stack->capacity--;
    }
}

int size(stack_list_t *stack)
{
    return stack->capacity;
}

void showTopElement(stack_list_t *stack)
{
    list_t *entry = stack->top;
    int topElement = entry->value;
    printf("TOP ELEMENT IS %d\n", topElement);
    return;
}

int main()
{
    stack_list_t *stack = allocStack();
    push(stack, 1);
    for (int i = 0; i < 20; i++)
    {
        push(stack, i);
        showTopElement(stack);
    }
    printf("####################################################\n");
    for (int i = 0; i < 20; i++)
    {
        showTopElement(stack);
        pop(stack);
    }
    return 0;
}