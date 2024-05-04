/*
Дан массив из 10 элементов. Определить, какое число в массиве встречается чаще всего. Гарантируется, что такое число ровно 1.
*/
#include <stdio.h>
#define SIZE 10

void input(int* arr);
int fPopular(int* arr);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    printf("%d",fPopular(arr));
    return 0;
}

void input(int* arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}

int fPopular(int* arr)
{
    int buff[SIZE] = {0}, popIdx = 0, MaxCnt = 0, cnt;
    for(int i = 0; i < SIZE; i++)
    {
        buff[i]=arr[i];
        cnt = 0;
        for(int j = 0; j < SIZE; j++)
            if(buff[i] == arr [j])
                cnt++;
        if (cnt > MaxCnt)
        {
            MaxCnt = cnt;
            popIdx = i;
        }
    }
    return buff[popIdx];
}
