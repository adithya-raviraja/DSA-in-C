#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_basic_s
{
    int top;
    int capacity;
    int *stackArr;
} stack_basic_t;

stack_basic_t *allocStack(int size)
{
    stack_basic_t *stack = (stack_basic_t *)malloc(sizeof(stack_basic_t));
    if (stack == NULL)
    {
        printf("Failed to alloc mem for stack\n");
        return NULL;
    }
    stack->capacity = size;
    stack->top = -1;
    int *arr = (int *)malloc(sizeof(stack->capacity * sizeof(int)));
    if (arr == NULL)
    {
        printf("Failed to alloc mem for array\n");
        free(stack);
        return NULL;
    }
    stack->stackArr = arr;
    return stack;
}

void push(stack_basic_t *stack, int element)
{
    if (stack->capacity - 1 == stack->top)
    {
        printf("Max limit of stack reached\n");
        return;
    }
    stack->top++;
    stack->stackArr[stack->top] = element;
    return;
}

void pop(stack_basic_t *stack)
{
    if (stack->top >= 0)
        stack->top--;
    else
        printf("No elements in the stack\n");
    return;
}

int getTopEntry(stack_basic_t *stack, int *element)
{
    if (stack->top < 0)
    {
        printf("No elements in stack");
        return -1;
    }
    *element = stack->stackArr[stack->top];
    printf("TOP ELEMENT IS %d\n", *element);
    return 0;
}

void reallocStack(stack_basic_t *stack, int newCapacity)
{
    stack->capacity = newCapacity;
    stack->stackArr = (int *)realloc(stack->stackArr, stack->capacity * sizeof(int));
    return;
}

int main()
{
    stack_basic_t *stack = allocStack(10);
    int topEntry = 0;
    int ret = 0;
    if (!stack)
        return -1;
    ret = getTopEntry(stack, &topEntry);
    reallocStack(stack, 20);
    for (int i = 0; i < 22; i++)
    {
        push(stack, i);
        ret = getTopEntry(stack, &topEntry);
    }
    printf("##################################################\n");
    for (int i = 0; i < 22; i++)
    {
        ret = getTopEntry(stack, &topEntry);
        pop(stack);
    }
    // ret = getTopEntry(stack, &topEntry);
    return 0;
}