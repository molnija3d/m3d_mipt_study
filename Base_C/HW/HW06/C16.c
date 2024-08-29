#include <stdio.h>
#include <inttypes.h>
/*
Составить функцию логическую функцию, которая определяет, верно ли, что число простое. Используя функцию решить задачу.
int is_prime(int n)
 */

int32_t is_prime(int32_t a);

int main(void)
{
    int32_t a;
    scanf("%"SCNd32,&a);
    printf(is_prime(a)? "YES\n" : "NO\n");
    return 0;
}


int32_t is_prime(int32_t a)
{
    int32_t num=a,i=1;
    if(num>3)
        while(i*i < a)
        {
            i++;
            if(a%i == 0)
            {
                return 0;
            }
        }
    if(a<2)
        return 0;
    return 1;
}

