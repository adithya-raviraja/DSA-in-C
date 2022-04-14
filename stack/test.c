#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j = 1;
    for (i = 1; i <= 10; i++)
    {
        while (j <= 10)
        {
            if (j == i)
            {
                j++;
                continue;
            }
            printf("J %d\n", j);
            j++;
        }
        j = 1;
        printf("######################################\n");
    }
}