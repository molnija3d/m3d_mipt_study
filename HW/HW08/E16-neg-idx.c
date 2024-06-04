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
    int frq[500] = {0};   //массив на 500 элементов; индексы - значения чисел из входящей последовательности
                                         //значение элемента массива - частота, с которой встречается число
    int* frqncy = frq + 250;            //помещаем указатель в середину мамссива, чтобы можно было использовать отрицательные индексы (числа)
    
    int mxIdx = arr[0];  //начальным значением, может быть любое число из входных данных
    
    for (int i = 0; i < SIZE; i++)
    {
        frqncy[arr[i]]++;    // возможен выход за границы массива на числах больше/меньше 249/-250
        if (frqncy[arr[i]] > frqncy[mxIdx])
            mxIdx = arr[i]; 
    }
    return mxIdx; 
}
