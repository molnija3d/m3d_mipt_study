/*
Сумма минимальна
Дан целочисленный массив из 30 элементов. Элементы массива могут принимать произвольные целые значения помещающиеся в int.
Необходимо создать функцию, которая находит и выводит в порядке возрастания номера двух элементов массива, сумма которых минимальна.
Input format
Последовательность из 30 целых чисел через пробел
Output format
Два целых числа через пробел
*/

#include <stdio.h>
#include <inttypes.h>
#define SIZE 30

void inparr(int32_t* arr,int32_t n);
void find_pos(int size, int a[]);

int main(void)
{
    int32_t nums[SIZE];
    inparr(nums,SIZE);
    find_pos(SIZE, nums);
    return 0;
}
void inparr(int32_t* arr,int32_t n)
{

    for(int i = 0; i < n ; i++)
        scanf("%d",&arr[i]);
}

void find_pos(int size, int a[])
{
    int minA=a[0], minB=a[1], posA=0, posB=1;
    for(int i=0; i < size; i++)
        for(int j=i+1; j<size; j++)
            if(a[i]+a[j]< minA+minB)
            {
                minA=a[i];
                posA=i;
                minB=a[j];
                posB=j;
            }


    posA < posB ? printf("%d %d\n",  posA, posB) : printf("%d %d\n", posB, posA);
}

