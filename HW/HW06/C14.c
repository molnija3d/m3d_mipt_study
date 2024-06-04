#include <stdio.h>
#include <inttypes.h>
/*
 *Составить функцию логическую функцию, которая определяет, верно ли, что сумма его цифр – четное число. Используя эту функцию решить задачу.
 */

char* iseven(int32_t a);

int main(void)
{
    int32_t a;
    scanf("%"SCNd32,&a);
    printf("%s\n",iseven(a));
    return 0;
}


char* iseven(int32_t a)
{
    int32_t sum=0, num=a;
    do
    {
        sum += num%10;
    }
    while(num/=10);
    if(sum%2 == 0)
        return "YES";
    return "NO";
}

