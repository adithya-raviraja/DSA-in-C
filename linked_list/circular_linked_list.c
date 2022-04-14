#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int g_firstEntry = true;

typedef struct listCcGeneric_S
{
    int value;
    void *next; // listCcGeneric_T
} listCcGeneric_T;

int getListSizeAndContents(int *size, listCcGeneric_T *mainList)
{
    listCcGeneric_T *cur = mainList;
    int entryCount = 0;
    if (mainList == NULL)
    {
        printf("MAIN LIST IS NULL\n");
        *size = 0;
        return 0;
    }
    do
    {
        printf("ENTRY %d: %d\n", entryCount, cur->value);
        entryCount++;
        cur = (listCcGeneric_T *)cur->next;
    } while (mainList->value != cur->value);

    *size = entryCount;
    printf("TOTAL_SIZE: %d\n", *size);
    return 0;
}

int insertValueInner(int value, listCcGeneric_T **mainList, int pos)
{
    listCcGeneric_T *entry = (listCcGeneric_T *)malloc(sizeof(listCcGeneric_T));
    listCcGeneric_T *cur = NULL;
    listCcGeneric_T *nextEntry = NULL;
    listCcGeneric_T *prevEntry = NULL;
    if (entry == NULL)
    {
        printf("Failed to allocate mem for adding list");
        return 1;
    }
    entry->value = value;
    entry->next = entry;
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
            cur = *mainList;
            do
            {
                prevEntry = cur;
                cur = (listCcGeneric_T *)cur->next;
            } while ((*mainList)->value != cur->value);
            entry->next = *mainList;
            cur->next = entry;
            *mainList = entry;
            return 0;
        }
        else if (pos == -1) // end
        {
            cur = *mainList;
            do
            {
                prevEntry = cur;
                cur = (listCcGeneric_T *)cur->next;
            } while ((*mainList)->value != cur->value);
            cur = entry;
            entry->next = prevEntry->next;
            prevEntry->next = entry;

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

void deleteValueInner(int pos, listCcGeneric_T **mainList)
{
    listCcGeneric_T *tempNode = *mainList;
    listCcGeneric_T *cur = *mainList;
    if (mainList == NULL)
    {
        printf("MAIN LIST IS NULL\n");
        return;
    }
    if (pos == 0) // delete first
    {
        while (*mainList != cur->next)
        {
            cur = (listCcGeneric_T *)cur->next;
        }
        cur->next = (*mainList)->next;
        *mainList = (*mainList)->next;
        free(tempNode);
    }
    else if (pos == -1) // delete last
    {
        listCcGeneric_T *lastButOne = NULL;
        while (*mainList != cur->next)
        {
            lastButOne = cur;
            printf("lastButOne value: %d\n", lastButOne->value);
            cur = (listCcGeneric_T *)cur->next;
        }
        lastButOne->next = *mainList;
        free(cur);
    }
    else // delete any
    {
        listCcGeneric_T *cur = *mainList;
        listCcGeneric_T *lastButOne = NULL;
        listCcGeneric_T *curNext = *mainList;
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

void deleteValues(listCcGeneric_T **mainList)
{
    deleteValueInner(0, mainList);
    deleteValueInner(-1, mainList);
    return;
}

int insertValues(listCcGeneric_T **mainList)
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
    return ret;
}

int main()
{
    listCcGeneric_T *mainList = NULL;
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