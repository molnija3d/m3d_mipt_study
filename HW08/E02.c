/*
Найти минимум
Ввести c клавиатуры массив из 5 элементов, найти минимальный из них.
Input format
5 целых чисел через пробел
Output format
Одно единственное целое число
*/
#include <stdio.h>
#define SIZE 5

void input(int *arr);
int min(int *arr);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    printf("%d\n",min(arr));
    return 0;
}

void input(int *arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}

int min(int *arr)
{
    int min = arr[0];
    for(int i=1; i<SIZE; i++)
        if(min > *(arr+i))
            min=*(arr+i);
    return min;
}
