/*
Кратность прежде всего
В диапазоне натуральных чисел от 2 до N определить, сколько из них кратны любому из чисел в диапазоне от 2 до 9.
Input format
Одно целое число N большее 2 и не превосходящее 10000
Output format
Все числа от 2 до 9 в формате: 
2 количество чисел кратных 2 
3 количество чисел кратных 3 
4 количество чисел кратных 4 
5 количество чисел кратных 5 
6 количество чисел кратных 6 
7 количество чисел кратных 7 
8 количество чисел кратных 8 
9 количество чисел кратных 9
*/

#include <stdio.h>

void findMulti(int num, int* arr);
void printArr(int* arr,int num);

int main(void)
{
    int num, arr[8];
    scanf("%d",&num);    
    findMulti(num,arr);
    printArr(arr,8);
    return 0;
}

void findMulti(int num,int *arr)
{
  int cnt; 
 
       for(int j = 2; j<10;j++)
       {
        cnt = 0;
         for(int i = 2; i <= num; i++)
           if(i%j == 0)
             arr[j-2]=++cnt;
             
       }
}
void printArr(int* arr,int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("%d %d\n",i+2,arr[i]);
    }
}
