/*
Больше среднего
Определить количество положительных элементов квадратной матрицы, превышающих по величине среднее арифметическое всех элементов главной диагонали.
Реализовать функцию среднее арифметическое главной диагонали.
Input format
5 строк по 5 целых чисел через пробел
Output format
Одно целое число
*/

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>


#define SIZE 5


float countAverageMatrix(int32_t** mtr, int n);
int32_t countAbove(int32_t** mtr, int n);
void inparr(int32_t** arr,int32_t n);

int main(void)
{
    int32_t** arr;
    arr = (int32_t**)malloc(SIZE*sizeof(int32_t*));
    for(int i=0; i<SIZE;i++)
      arr[i]=(int32_t*)malloc(SIZE*sizeof(int32_t));

    inparr(arr,SIZE);
    printf("%"PRId32,countAbove(arr,5));
    free(arr);
    return 0;
}

float countAverageMatrix(int32_t** mtr, int n)
{
    int sum=0;
    for(int i=0; i<n; ++i)
        sum+=mtr[i][i];

    return sum/5.;
}

int32_t countAbove(int32_t** mtr, int n)
{
    float avg = countAverageMatrix(mtr,n);
    int cnt = 0;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(mtr[i][j]>avg)
                cnt++;

    return cnt;
}

void inparr(int32_t** arr,int32_t n)
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            scanf("%"SCNd32,&arr[i][j]);

}
