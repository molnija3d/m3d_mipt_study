/*
Максимум и минимум
Считать массив из 10 элементов и найти в нем максимальный и минимальный элементы и их номера.
Input format
10 целых чисел через пробел
Output format
4 целых числа через пробел: номер максимума, максимум, номер минимума, минимум
*/
#include <stdio.h>
#define SIZE 10

void input(int *arr);
void MinMax(int *arr);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    MinMax(arr);
    return 0;
}

void input(int *arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}

void MinMax(int *arr)
{
    int min = arr [0], max = arr[0];
    int minN = 0, maxN = 0;
    for(int i=1; i<SIZE; i++)
    {
        if(min > arr[i])
        {
            min = arr[i];
            minN = i;
        }
        if (max < arr[i])
        {
            max = arr[i];
            maxN = i;
        }
    }
    printf("%d %d %d %d\n", maxN + 1, max, minN + 1, min);
}
