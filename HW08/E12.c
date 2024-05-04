/*
По убыванию и по возрастанию
Считать массив из 10 элементов и отсортировать первую половину по возрастанию, а вторую – по убыванию.
Input format
10 целых чисел через пробел
Output format
Исходный массив. Первая часть отсортирована по возрастанию, вторая половина по убыванию.
*/
#include <stdio.h>
#define SIZE 10

void input(int *arr);
void print(int *arr);
void sortFrstDsc(int *arr);
void sortScndAsc(int *arr);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    sortFrstDsc(arr);
    sortScndAsc(arr);
    print(arr);
    return 0;
}

void input(int *arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}
void print(int *arr)
{
    for(int i=0; i< SIZE; i++)
        printf("%d ", arr[i]);
}

void sortFrstDsc(int *arr)

{
    int tmp = 0;
    for(int j = 0; j <SIZE/2; j++)
    {
        int isSorted = 1;
        for (int i = 0; i < SIZE/2-1-j; i++)
        {
            if(arr[i]>arr[i+1])
            {
                tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                isSorted = 0;
            }
        }
        if(isSorted)
            break;
    }
}

void sortScndAsc(int *arr)
{
    int tmp = 0;
    for(int j = 0; j <SIZE/2; j++)
    {
        int isSorted = 1;
        for (int i = SIZE/2; i < SIZE-1-j; i++)
        {
            if(arr[i]<arr[i+1])
            {
                tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                isSorted = 0;
            }
        }
        if(isSorted)
            break;
    }
}
