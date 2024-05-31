#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int arr[4][3] = {1, 2, 3,
                     4, 5, 6,
                     7, 8, 9,
                     10,11,12};

    ///////////////////////////////////////////
    int(*(tmp[4]))[3];
    int(*tmp2)[3];
    /////////////////////////////////////////////
    for (int i = 0; i < 4; i++)
    {
        tmp[i] = &arr[i];
    }
    //////////////////////////////////////////
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // printf("%2d ", (*tmp[i])[j]);
            printf("%2d ", *(**(tmp + i) + j));
        }
        printf("\n");
    }
    printf("\n");
    //////////////////////////////////
    tmp2 = tmp[1];
    tmp[1] = tmp[2];
    tmp[2] = tmp2;
    ///////////////////////////////////
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // printf("%2d ", (*tmp[i])[j]);
            printf("%2d ", *(**(tmp + i) + j));
        }
        printf("\n");
    }
    return 0;
}