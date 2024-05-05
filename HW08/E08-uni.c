/*
»нверси€ каждой трети
—читать массив из 12 элементов и выполнить инверсию дл€ каждой трети массива.
Input format
12 целых чисел через пробел
Output format
12 целых чисел через пробел
*/
#include <stdio.h>
#define SIZE 12

void input(int *arr);
void print(int *arr);
void inverse(int *arr, int frmIdx, int toIdx);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    inverse(arr,0,SIZE/3);
    inverse(arr,SIZE/3,2*SIZE/3);
    inverse(arr,2*SIZE/3,SIZE);
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
void inverse(int *arr, int frmIdx, int toIdx)
{
    int tmp, maxIdx ;
    maxIdx = (toIdx-frmIdx)/2 + frmIdx;

    for(int i=frmIdx; i<maxIdx; i++)
    {
        tmp = arr[toIdx + frmIdx - 1 - i];
        arr[toIdx + frmIdx - 1 - i] = arr[i];
        arr[i] = tmp;
    }
}
