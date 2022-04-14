// Reverse a linked list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g_firstEntry = 0;

struct List
{
    int value;
    struct List *next; // List
};

void insertValues(int value, struct List **mainList)
{
    struct List *entry = NULL;
    struct List *cur = NULL;
    entry = (struct List *)malloc(sizeof(struct List));
    if (entry == NULL)
    {
        printf("FAILED TO ALLOC MEMEMORY");
        return;
    }
    if (g_firstEntry == 0)
    {
        entry->value = value;
        entry->next = NULL;
        *mainList = entry;
        g_firstEntry = 1;
    }
    else
    {
        entry->value = value;
        entry->next = NULL;
        cur = *mainList;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = entry;
    }
}

void printValuesInMainList(struct List **mainList)
{
    struct List *entry = NULL;
    int counter = 0;
    for (entry = *mainList; entry != NULL; entry = entry->next)
    {
        ++counter;
        printf("VALUE %d: %d\n", counter, entry->value);
    }
}

struct List *reverseList(struct List *head)
{
    struct List *cur = head;
    struct List *nextEntry = NULL;
    struct List *temp = NULL;

    if (!head)
    {
        return;
    }
    else
    {
        temp = head->next;
        head->next = temp->next;
        temp->next = head;
        head = temp;
        head->next->next = reverseList(head->next->next);
        return head;
    }
}

void insertValuesToList(struct List **mainList)
{
    struct List *list1 = NULL;
    struct List *list2 = NULL;
    insertValues(2, mainList);
    insertValues(3, mainList);
    insertValues(5, mainList);
    insertValues(7, mainList);
    insertValues(11, mainList);
    insertValues(12, mainList);
    printValuesInMainList(mainList);
}

int main()
{
    struct List *mainList = NULL;
    struct List *mainListRev = NULL;
    insertValuesToList(&mainList);
    mainList = reverseList(mainList);
    printValuesInMainList(&mainList);
    return 0;
}