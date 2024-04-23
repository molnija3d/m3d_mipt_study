#include <stdio.h>
#include <inttypes.h>
/*Ввести два целых числа a и b (a ≤ b) и вывести квадраты всех чисел от a до b.*/

int main(void)
{
    int32_t a,b;
    scanf("%"SCNd32"%"SCNd32,&a,&b);
    for(int i=a;i<=b;i++)
    {
      printf("%"PRId32" ",i*i);    
    }
    
    return 0;
}
