/*
Массив максимумов
Дана целочисленная квадратная матрица 10 х 10. реализовать алгоритм вычисления суммы максимальных элементов из каждой строки. 
Напечатать значение этой суммы. 
Предполагается, что в каждой строке такой элемент единственный. Реализовать функцию поиска максимума в строке из 10 элементов
Input format
10 строк состоящих из 10 целых чисел через пробел.
Output format
Одно целое число
*/

#include <stdio.h>
#include <inttypes.h>

#define SIZE 10

void inparr(int32_t arr[][SIZE],int32_t n);
int32_t countSumMax(int32_t mtr[][SIZE], int n);
int32_t countMax(int32_t arr[SIZE], int n);

int main(void)
{
    int32_t arr[SIZE][SIZE]={0};

    inparr(arr,SIZE);
    printf("%d",countSumMax(arr,SIZE));
    return 0;
}

int32_t countSumMax(int32_t mtr[][SIZE], int n)
{ 
 int sum=0;
  for(int i=0; i<n; ++i)
      sum+=countMax(mtr[i],n);

  return sum;
}

int32_t countMax(int32_t arr[SIZE], int n)
{
   
    int max=arr[0];
    for(int i=0;i<n;i++)
    {
      if(arr[i]>max)
       max=arr[i];
    }
    return max;
}

void inparr(int32_t arr[][SIZE],int32_t n)
{
    for(int i=0; i<n;i++)
     for(int j=0; j<n;j++)
       scanf("%d",&arr[i][j]);
}
