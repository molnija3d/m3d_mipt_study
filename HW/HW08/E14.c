/*
Более одного раза
Считать массив из 10 элементов и выделить в другой массив все числа, которые встречаются более одного раза.
В результирующем массиве эти числа не должны повторяться.
Input format
10 целых чисел через пробел
Output format
Целые числа через пробел, которые встречаются более одного раза в исходном массиве.
*/
#include <stdio.h>
#define SIZE 10

void input(int* arr);
void print(int* arr, int n);
int findTwcDgt(int* arr, int* res);
_Bool isTwice(int* arr, int idx);
_Bool notInRes(int* res, int val, int cnt);


int main(void)
{
    int arr[SIZE] = {0}, res[SIZE] = {0}, n = 0;
    input(arr);
    n = findTwcDgt(arr,res);
    print(res,n);
    return 0;
}

void input(int* arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}
void print(int* arr, int n)
{
    for(int i=0; i< n; i++)
        printf("%d ", arr[i]);
}

int findTwcDgt(int* arr, int *res)
{
    int cnt = 0 ;
    for(int i = 0; i <SIZE; i++)
        if(isTwice(arr,i) && notInRes(res,arr[i],cnt))
            res[cnt++] = arr[i];
    return cnt;
}

_Bool isTwice(int* arr, int idx)
{
    for(int i = idx + 1; i < SIZE; i++)
        if(arr[idx] == arr[i])
            return 1;
    return 0;
}

_Bool notInRes(int* res, int val, int cnt)
{
    for(int i = 0; i < cnt; i++)
    {
        if( res[i] == val)
            return 0;
    }
    return 1;
}
