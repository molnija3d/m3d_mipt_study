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
void inverse(int *arr);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    inverse(arr);
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
void inverse(int *arr)
{
    int tmp[SIZE]= {0},
        hSizeBtm = SIZE/2,
        hSizeTop = SIZE + SIZE/2;

    for(int i=0; i<hSizeBtm; i++)
        tmp[i] = arr[hSizeBtm - 1 - i];

    for(int i=SIZE/2; i<SIZE; i++)
        tmp[i] = arr[hSizeTop - 1 - i];

    for(int i=0; i<SIZE; i++)
        arr[i] = tmp[i];

}
