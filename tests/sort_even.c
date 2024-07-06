

#include <stdio.h>
#define STR_SIZE 100
void sort_even_odd(int n, int a[])
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] % 2 != 0)
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    for (int i = n / 2, j = n - 1; i < n - n/4; i++, j--)
    {      
        int temp = a[j];
        a[j] = a[i];
        a[i] = temp;
    }
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main()
{
    int arr[20] = {20, 19, 27, 11, 17, 15, 24, 22, 31, 2, 3, 4, 8, 6, 1, 14, 18, 34, 35, 33};
    sort_even_odd(20, arr);
    return 0;
}
