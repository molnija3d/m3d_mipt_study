/*
Сумма положительных элементов
Считать массив из 10 элементов и посчитать сумму положительных элементов массива.
Input format
10 целых чисел через пробел
Output format
Одно целое число - сумма положительных элементов массива
*/
#include <stdio.h>
#define SIZE 10

void input(int *arr);
void pozSum(int *arr);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    pozSum(arr);
    return 0;
}

void input(int *arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}

void pozSum(int *arr)
{
    int sum=0;
    
    for(int i=0; i<SIZE; i++)
    {
      if(arr[i] > 0)
         sum += *(arr+i);
    }
    printf("%d\n", sum);
}
