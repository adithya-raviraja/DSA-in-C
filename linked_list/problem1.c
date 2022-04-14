/* Split a circular linked list into two equal parts. If the number of nodes in the list are odd
 * make first list one node extra than second list.
 * eg {2,3,5,7,11} should yield two lists {2,3,5} and {7,11}
 * eg {4,5,6,7,8,9} should yield two lists {4,5,6} and {7,8,9}
 */
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

void breakMainList(struct List **mainList, struct List **list1, struct List **list2)
{
    struct List *slowPtr = *mainList;
    struct List *slowPtrNext = NULL;
    struct List *fastPtr = (*mainList)->next;
    while (fastPtr != NULL && fastPtr->next != NULL)
    {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
    }
    if (fastPtr)
    {
        *list1 = *mainList;
        slowPtrNext = slowPtr->next;
        slowPtr->next = *list1;
        *list2 = slowPtrNext;
        fastPtr->next = *list2;
    }
    else
    {
        *list1 = *mainList;
        slowPtrNext = slowPtr->next;
        slowPtr->next = *list1;
        *list2 = slowPtrNext;
        while (slowPtrNext->next != NULL)
        {
            slowPtrNext = slowPtrNext->next;
        }
        slowPtrNext->next = *list2;
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

void printValuesInSubList(struct List **list1, struct List **list2)
{
    struct List *cur = *list1;
    do
    {
        printf("VAL in List1: %d\n", cur->value);
        cur = cur->next;
    } while (cur->value != (*list1)->value);
    cur = *list2;
    do
    {
        printf("VAL in List2: %d\n", cur->value);
        cur = cur->next;
    } while (cur->value != (*list2)->value);
}

void insertValuesToList(char *testCase, struct List **mainList)
{
    struct List *list1 = NULL;
    struct List *list2 = NULL;
    if (strcmp(testCase, "TESTCASE1") == 0)
    {
        insertValues(2, mainList);
        insertValues(3, mainList);
        insertValues(5, mainList);
        insertValues(7, mainList);
        insertValues(11, mainList);
        printValuesInMainList(mainList);
        breakMainList(mainList, &list1, &list2);
        printValuesInSubList(&list1, &list2);
    }
    if (strcmp(testCase, "TESTCASE2") == 0)
    {
        insertValues(4, mainList);
        insertValues(5, mainList);
        insertValues(6, mainList);
        insertValues(7, mainList);
        insertValues(8, mainList);
        insertValues(9, mainList);
        printValuesInMainList(mainList);
        breakMainList(mainList, &list1, &list2);
        printValuesInSubList(&list1, &list2);
    }
    return;
}

int main()
{
    struct List *mainList = NULL;
    printf("**********************************CASE1************************************\n");
    insertValuesToList("TESTCASE1", &mainList);
    printf("**********************************END************************************\n");
    printf("**********************************CASE2************************************\n");
    mainList = NULL;
    g_firstEntry = 0;
    insertValuesToList("TESTCASE2", &mainList);
    printf("**********************************END************************************\n");
    return 0;
}