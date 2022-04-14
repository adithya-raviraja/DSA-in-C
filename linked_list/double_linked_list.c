#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int g_firstEntry = true;

typedef struct listDoubleGeneric_S
{
    int value;
    void *next; // listDoubleGeneric_T
    void *prev; // listDoubleGeneric_T
} listDoubleGeneric_T;

int getListSizeAndContents(int *size, listDoubleGeneric_T *mainList)
{
    listDoubleGeneric_T *singleEntry = NULL;
    listDoubleGeneric_T *lastEntry = NULL;
    int entryCount = 0;
    if (mainList == NULL)
    {
        printf("MAIN LIST IS NULL\n");
        *size = 0;
        return 0;
    }
    for (singleEntry = mainList; singleEntry != NULL; singleEntry = (listDoubleGeneric_T *)singleEntry->next)
    {
        printf("ENTRY %d: %d\n", entryCount, singleEntry->value);
        lastEntry = singleEntry;
        entryCount++;
    }
    entryCount = 0;
    for (singleEntry = lastEntry; singleEntry != NULL; singleEntry = (listDoubleGeneric_T *)singleEntry->prev)
    {
        printf("REV_ENTRY %d: %d\n", entryCount, singleEntry->value);
        entryCount++;
    }
    *size = entryCount;
    printf("TOTAL_SIZE: %d\n", *size);
    return 0;
}

int insertValueInner(int value, listDoubleGeneric_T **mainList, int pos)
{
    listDoubleGeneric_T *entry = (listDoubleGeneric_T *)malloc(sizeof(listDoubleGeneric_T));
    listDoubleGeneric_T *cur = NULL;
    listDoubleGeneric_T *lastEntry = NULL;
    listDoubleGeneric_T *nextEntry = NULL;
    listDoubleGeneric_T *prevEntry = NULL;
    if (entry == NULL)
    {
        printf("Failed to allocate mem for adding list");
        return 1;
    }
    entry->value = value;
    entry->next = NULL;
    entry->prev = NULL;
    if (g_firstEntry == true)
    {
        *mainList = entry;
        g_firstEntry = false;
        return 0;
    }
    else
    {
        if (pos == 0) // beginning
        {
            entry->next = *mainList;
            (*mainList)->prev = entry;
            *mainList = entry;
            return 0;
        }
        else if (pos == -1) // end
        {
            cur = *mainList;
            while (cur->next != NULL)
            {
                cur = cur->next;
            }
            cur->next = entry;
            entry->prev = cur;
            return 0;
        }
        else // any position
        {
            cur = *mainList;
            while (cur->next != NULL)
            {
                cur = cur->next;
                if (pos == 1)
                    break;
                pos--;
            }
            if (pos != 1)
            {
                printf("POSITION DOES NOT EXIST IN LIST\n");
                free(entry);
                return 0;
            }
            nextEntry = cur;
            prevEntry = cur->prev;
            cur = entry;
            entry->next = nextEntry;
            entry->prev = nextEntry->prev;
            prevEntry->next = entry;
            if (nextEntry != NULL)
                nextEntry->prev = entry;
            return 0;
        }
    }
}

void deleteValueInner(int pos, listDoubleGeneric_T **mainList)
{
    listDoubleGeneric_T *tempNode = *mainList;
    if (mainList == NULL)
    {
        printf("MAIN LIST IS NULL\n");
        return;
    }
    if (pos == 0) // delete first
    {
        *mainList = (*mainList)->next;
        (*mainList)->prev = NULL;
        free(tempNode);
    }
    else if (pos == -1) // delete last
    {
        listDoubleGeneric_T *cur = *mainList;
        listDoubleGeneric_T *lastButOne = NULL;
        while (cur->next != NULL)
        {
            lastButOne = cur;
            cur = cur->next;
        }
        lastButOne->next = NULL;
        free(cur);
    }
    else // delete any
    {
        listDoubleGeneric_T *cur = *mainList;
        listDoubleGeneric_T *lastButOne = NULL;
        listDoubleGeneric_T *curNext = *mainList;
        listDoubleGeneric_T *prevEntry = NULL;
        listDoubleGeneric_T *nextEntry = NULL;
        while (cur->next != NULL)
        {
            lastButOne = cur;
            cur = cur->next;
            pos--;
            if (pos == 0)
                break;
        }
        if (pos != 0)
        {
            printf("POSITION DOES NOT EXIST IN LIST\n");
            return;
        }
        lastButOne->next = cur->next;
        nextEntry = cur->next;
        nextEntry->prev = lastButOne;
        free(cur);
        return;
    }
    return;
}

void deleteValues(listDoubleGeneric_T **mainList)
{
    deleteValueInner(0, mainList);
    deleteValueInner(-1, mainList);
    deleteValueInner(2, mainList);
    return;
}

int insertValues(listDoubleGeneric_T **mainList)
{
    int ret = 0;

    ret = insertValueInner(1, mainList, 0);
    if (ret != 0)
    {
        printf("Failed to add entry %d to list", 1);
        return ret;
    }
    ret = insertValueInner(2, mainList, 0);
    if (ret != 0)
    {
        printf("Failed to add entry %d to list", 2);
        return ret;
    }
    ret = insertValueInner(3, mainList, -1);
    if (ret != 0)
    {
        printf("Failed to add entry %d to list", 3);
        return ret;
    }

    ret = insertValueInner(4, mainList, -1);
    if (ret != 0)
    {
        printf("Failed to add entry %d to list", 4);
        return ret;
    }

    ret = insertValueInner(7, mainList, 3);
    if (ret != 0)
    {
        printf("Failed to add entry %d to list", 7);
        return ret;
    }

    ret = insertValueInner(8, mainList, -1);
    if (ret != 0)
    {
        printf("Failed to add entry %d to list", 8);
        return ret;
    }
    ret = insertValueInner(9, mainList, -1);
    if (ret != 0)
    {
        printf("Failed to add entry %d to list", 9);
        return ret;
    }

    return ret;
}

int main()
{
    listDoubleGeneric_T *mainList = NULL;
    int totalSize = 0;
    int ret = 0;
    ret = insertValues(&mainList);
    if (ret != 0)
    {
        printf("Failed to add required entries");
        return 1;
    }
    printf("*****POST_INSERT*****\n");
    getListSizeAndContents(&totalSize, mainList);
    deleteValues(&mainList);
    printf("*****POST DELETE*****\n");
    getListSizeAndContents(&totalSize, mainList);
    return 0;
}