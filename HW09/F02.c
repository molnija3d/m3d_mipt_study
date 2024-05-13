/*
Четные в начало
Написать только одну функцию, которая ставит в начало массива все четные элементы, а в конец – все нечетные. 
Не нарушайте порядок следования чисел между собой. Строго согласно прототипу:.
void sort_even_odd(int n, int a[])
Input format
Функцийя принмате на вход целые числа
Output format
Отсортированный исходный массив
*/
/*
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>

void inparr(int32_t* arr,int32_t n);
void printarr(int32_t* arr,int32_t n);;
void sort_even_odd(int n, int a[]);
int main(void)
{
    int a[20]={0};
    inparr(a,20);
    printarr(a,20);
    sort_even_odd(20,a);
    printarr(a,20);
    return 0;
}
*/
void sort_even_odd(int n, int a[])
{
    int buff[n],cnt=0;
    for(int i=0; i<n; i++)
     if(a[i]%2==0)
      buff[cnt++]=a[i];
      
    for(int i=0; i<n; i++)
     if(a[i]%2!=0)
      buff[cnt++]=a[i];
    
    for(int i=0; i<n; i++)
      a[i]=buff[i];
}
/*
void inparr(int32_t* arr,int32_t n)
{
    srand(time(NULL));
    for(int i = 0; i < n ; i++)
        arr[i]=rand()%100;
}
void printarr(int32_t* arr,int32_t n)
{
    for (int i = 0; i < n; i++)
        printf("%3d",arr[i]);
        
    printf("\n");
}
*/
