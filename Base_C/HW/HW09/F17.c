/*
След матрицы
Составить функцию которая находит след матрицы в двумерном массиве.
Показать пример ее работы на матрице из 5 на 5 элементов. След матрицы - это сумма элементов на главной диагонали.
Input format
25 целых чисел через пробел.
Output format
Одно целое число.
*/

#include <stdio.h>
#include <inttypes.h>

#define SIZE 5


int32_t countMatrix(int32_t mtr[][SIZE], int n);
void inparr(int32_t arr[][SIZE],int32_t n);

int main(void)
{
    int32_t arr[SIZE][SIZE]= {0};

    inparr(arr,SIZE);
    printf("%"PRId32,countMatrix(arr,SIZE));
    return 0;
}

int countMatrix(int32_t mtr[][SIZE], int n)
{
    int sum=0;
    for(int i=0; i<n; ++i)
    {
        sum+=mtr[i][i];
    }
    return sum;
}
void inparr(int32_t arr[][SIZE],int32_t n)
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            scanf("%"SCNd32,&arr[i][j]);
        }
}

