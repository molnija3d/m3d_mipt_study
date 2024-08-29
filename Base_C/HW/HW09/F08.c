/*
Пропущенное число
В последовательности записаны целые числа от M до N ( M меньше N, M больше или равно 1)в произвольном порядке, но одно из чисел пропущено
(остальные встречаются ровно по одному разу). N не превосходит 1000. Последовательность заканчивается числом 0. Определить пропущенное число.
Input format
Последовательность целых чисел от M до N. M, N не превосходит 1000.
Output format
Одно целое число
*/
#include <stdio.h>
#include <inttypes.h>

#define SIZE 1000

int32_t findLost(int32_t* arr,int32_t n);
void inparr(int32_t* arr,int32_t n);
void sort(int32_t* arr,int32_t n);

int main(void)
{
    int32_t arr[SIZE]= {0};
    inparr(arr,SIZE);
    printf("%d",findLost(arr,SIZE));
    return 0;
}

int32_t findLost(int32_t* arr,int32_t n)
{
    sort(arr,SIZE);
    for(int i=0; i<n && arr[i]; i++)
    {
        if(arr[i]+1 != arr[i+1])
            return arr[i]+1;
    }
    return 0;
}

void sort(int32_t* arr,int32_t n)
{
    int32_t buff;
    for(int i=0; i<n && arr[i]; i++)
        for (int j = i; j < n && arr[j]; j++)
        {
            if(arr[j]<arr[i])
            {
                buff=arr[i];
                arr[i]=arr[j];
                arr[j]=buff;
            }
        }
}

void inparr(int32_t* arr,int32_t n)
{
    int i=0;
    do
    {
        scanf("%d",&arr[i++]);
    }
    while(arr[i-1]);
}
