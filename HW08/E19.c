/*
Цифры по порядку
Вывести в порядке следования цифры, входящие в десятичную запись натурального числа N.
Input format
Одно натуральное число N
Output format
Цифры через пробел
*/

#include <stdio.h>

void printSep(int num);

int main(void)
{
    int num;
    scanf("%d",&num);
    printSep(num);
    return 0;
}

void printSep(int num)
{
   int arr[11] = {0}, cnt = 0; 
   do
   {
     arr[cnt++] = num%10;
   }
   while(num/=10);
   
   while(--cnt >= 0)
    printf("%d ", arr[cnt]);
}
