/*
»нверси€ каждой трети
—читать массив из 12 элементов и выполнить инверсию дл€ каждой трети массива.
Input format
12 целых чисел через пробел
Output format
12 целых чисел через пробел
*/
#include <stdio.h>
#define SIZE 12

void input(int *arr);
void print(int *arr);
void inverseThird(int *arr);

int main(void)
{
    int arr[SIZE] = {0};
    input(arr);
    inverseThird(arr);
    print(arr);
    return 0;
}

void input(int *arr)
{
    for(int i=0; i<SIZE; i++)
        scanf("%d",arr+i);
}
void print(int *arr)
{
    for(int i=0; i< SIZE; i++)
        printf("%d ", arr[i]);
}
void inverseThird(int *arr)
{
    int tmp[SIZE]= {0};

    for(int j = 0; j<3; j++)
    {
        int top = (j+1)*SIZE/3,
            btm = j*SIZE/3;
        for(int i=btm; i<top; i++)
           tmp[i] = arr[top + btm - 1 - i];
    }

    for(int i=0; i<SIZE; i++)
        arr[i] = tmp[i];

}
