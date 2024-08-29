/*
Четные и нечетные
Дан целочисленный массив из 10 элементов. Необходимо определить количество четных и нечетных чисел.
Если количество чётных чисел больше, чем количество нечётных, заменить каждое нечетное число на произведение нечетных цифр в его десятичной записи.
Если количество нечётных чисел больше или равно количеству чётных, заменить каждое чётное число на произведение чётных цифр в его десятичной записи.
Input format
10 целых чисел через пробел
Output format
10 целых чисел через пробел
*/

#include <stdio.h>
#include <inttypes.h>

#define SIZE 10

void inpArr(int32_t* arr,int32_t n);
void printArr(int32_t* arr,int32_t n);
void modArray(int32_t* arr,int32_t n);
int32_t mulSpareDgt(int32_t num);
int32_t mulEvenDgt(int32_t num);

int main(void)
{
    int32_t arr[SIZE]= {0};

    inpArr(arr,SIZE);
    modArray(arr,SIZE);
    printArr(arr,SIZE);
    return 0;
}

void modArray(int32_t* arr,int32_t n)
{
    int cntSpare=0,cntEven=0;
    for(int i = 0; i<n ; i++)
        arr[i]%2?++cntSpare:++cntEven;

    if(cntSpare >= cntEven)
    {
        for(int i =0; i<n; i++)
            if(arr[i]%2 == 0)
                arr[i] = mulEvenDgt(arr[i]);

    }
    else
        for(int i =0; i<n; i++)
            if(arr[i]%2)
                arr[i] = mulSpareDgt(arr[i]);

}

int32_t mulSpareDgt(int32_t num)
{
    int32_t mul=1;
    do
    {
        if(num%2)
            mul*=num%10;
    }
    while(num/=10);
    return mul;
}

int32_t mulEvenDgt(int32_t num)
{
    int32_t mul=1;
    do
    {
        if(!(num%2))
            mul*=num%10;
    }
    while(num/=10);
    return mul;
}
void inpArr(int32_t* arr,int32_t n)
{
    for(int i=0; i<n; i++)
        scanf("%"SCNd32,&arr[i]);
}

void printArr(int32_t* arr,int32_t n)
{
    for(int i=0; i<n; i++)
        printf("%"PRId32" ",arr[i]);
}

