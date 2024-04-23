#include <stdio.h>
#include <inttypes.h>
/*
Ввести натуральное число вывести квадраты и кубы всех чисел от 1 до этого числа. Число не превосходит 100.
*/

int main(void)
{
    int32_t a;
    scanf("%"SCNd32,&a);
    for(int i=1;i<=a;i++)
    {
      printf("%"PRId32" %"PRId32" %"PRId32"\n",i,i*i,i*i*i);    
    }
    
    return 0;
}
