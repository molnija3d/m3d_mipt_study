/*
Среднее арифметическое массива
Считать массив из 12 элементов и посчитать среднее арифметическое элементов массива.
Input format
12 целых чисел через пробел
Output format
Среднее арифметическое в формате "%.2f"
*/
#include <stdio.h>
#define SIZE 12

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
      sum += arr[i];
    
    printf("%.2f\n", (float)sum/SIZE);
}
