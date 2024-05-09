/*
Инверсия половинок
Считать массив из 10 элементов и выполнить инверсию отдельно для 1-ой и 2-ой половин массива.
Необходимо изменить считанный массив и напечатать его одним циклом.
Input format
10 целых элементов массива через пробел.
Output format
10 целых элементов массива через пробел.
*/
#include <stdio.h>
#define SIZE 10

void input(int *arr);
void print(int *arr);
void inverse(int *arr, int frmIdx, int toIdx);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    inverse(arr,0,SIZE/2);
    inverse(arr,SIZE/2,SIZE);
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
