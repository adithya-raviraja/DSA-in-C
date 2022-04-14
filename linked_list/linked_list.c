#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int g_firstEntry = true;

typedef struct listGeneric_S
{
    int value;
    void *next; // listGeneric_T
} listGeneric_T;

int getListSizeAndContents(int *size, listGeneric_T *mainList)
{
    listGeneric_T *singleEntry = NULL;
    int entryCount = 0;
    if (mainList == NULL)
    {
        printf("MAIN LIST IS NULL\n");
        *size = 0;
        return 0;
    }
    for (singleEntry = mainList; singleEntry != NULL; singleEntry = (listGeneric_T *)singleEntry->next)
    {
        printf("ENTRY %d: %d\n", entryCount, singleEntry->value);
        entryCount++;
    }
    *size = entryCount;
    printf("TOTAL_SIZE: %d\n", *size);
    return 0;
}

int insertValueInner(int value, listGeneric_T **mainList, int pos)
{
    listGeneric_T *entry = (listGeneric_T *)malloc(sizeof(listGeneric_T));
    listGeneric_T *cur = NULL;
    listGeneric_T *nextEntry = NULL;
    if (entry == NULL)
    {
        printf("Failed to allocate mem for adding list");
        return 1;
    }
    entry->value = value;
    entry->next = NULL;
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
            return 0;
        }
        else // any position
        {
            cur = *mainList;
            while (cur->next != NULL)
            {
                cur = cur->next;
                pos--;
                if (pos == 1)
                    break;
            }
            if (pos != 1)
            {
                printf("POSITION DOES NOT EXIST IN LIST\n");
                free(entry);
                return 0;
            }
            nextEntry = cur->next;
            cur->next = entry;
            entry->next = nextEntry;
            return 0;
        }
    }
}

void deleteValueInner(int pos, listGeneric_T **mainList)
{
    listGeneric_T *tempNode = *mainList;
    if (mainList == NULL)
    {
        printf("MAIN LIST IS NULL\n");
        return;
    }
    if (pos == 0) // delete first
    {
        *mainList = (*mainList)->next;
        free(tempNode);
    }
    else if (pos == -1) // delete last
    {
        listGeneric_T *cur = *mainList;
        listGeneric_T *lastButOne = NULL;
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
        listGeneric_T *cur = *mainList;
        listGeneric_T *lastButOne = NULL;
        listGeneric_T *curNext = *mainList;
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
        free(cur);
        return;
    }
    return;
}

void deleteValues(listGeneric_T **mainList)
{
    deleteValueInner(0, mainList);
    deleteValueInner(-1, mainList);
    deleteValueInner(2, mainList);
    return;
}

int insertValues(listGeneric_T **mainList)
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
    listGeneric_T *mainList = NULL;
    int totalSize = 0;
    int ret = 0;
    ret = insertValues(&mainList);
    if (ret != 0)
    {
        printf("Failed to add required entries");
        return 1;
    }
    getListSizeAndContents(&totalSize, mainList);
    deleteValues(&mainList);
    getListSizeAndContents(&totalSize, mainList);
    return 0;
}