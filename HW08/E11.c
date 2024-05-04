/*
ќтсортировать по последней цифре
—читать массив из 10 элементов и отсортировать его по последней цифре.
Input format
10 целых чисел через пробел
Output format
Ётот же массив отсортированный по последней цифре
*/
#include <stdio.h>
#define SIZE 10

void input(int *arr);
void print(int *arr);
void sortLDg(int *arr);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    sortLDg(arr);
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
void sortLDg(int *arr)
{
    int tmp = 0;
    for(int j = 0; j <SIZE; j++)
    {
        int isSorted = 1;
        for (int i = 0; i < SIZE-1-j; i++)
        {
            if((arr[i]%10)>(arr[i+1]%10))
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
