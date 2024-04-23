#include <stdio.h>
#include <inttypes.h>
/*
 *Составить функцию логическую функцию, которая определяет, верно ли, что в заданном числе все цифры стоят по возрастанию. Используя данную функцию решить задачу.
int grow_up(int n)
 */

int32_t grow_up(int32_t a);

int main(void)
{
    int32_t a;
    scanf("%"SCNd32,&a);
    printf("%s\n",(grow_up(a))? "YES" : "NO");
    return 0;
}


int32_t grow_up(int32_t a)
{
    int32_t num=a,prev=0,tmp;
    prev = num%10;
    while(num/=10)
    {
       tmp = num%10;
       if(prev <= tmp) return 0;
       prev = tmp;
    }
    return 1;
}
    
